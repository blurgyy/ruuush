-- @EXPECTED_RESULTS@: CORRECT
module Main where
-- running time: O(n log n)

-- Same approach as all the others: We sort on increasing quality/coordinate
-- r3, and add the points to a 2D pareto envelope in that order. We use a red
-- black tree to maintain the 2D pareto envelope, so we can easily find and
-- replace the part of the pareto envelope that is dominated by a new point.

import qualified Data.List as L
import           Data.Monoid
import           Data.Ord

-- Since the input size is huge we need to use text insteaf of regular String's

import qualified Data.Set as S
import qualified Data.Text as T
import qualified Data.Text.IO as TIO
import qualified Data.Text.Read as TR

import           Debug.Trace

main = TIO.interact $ T.pack . unlines . map (show . shortListSize) . readInput . tail . T.lines

type Point3 = (Int,Int,Int)
type Point2 = (Int,Int)
type PointSet3 = [Point3]


newtype PPoint = PPoint { unP :: Point2 } deriving (Show,Eq,Read)

-- compare by x-coord only
instance Ord PPoint where
  (PPoint (x,_)) `compare` (PPoint (x',_)) = x `compare` x'


-- | The pareto envelope is an x-monotone curve, so store the points ordered on x-coord
newtype ParetoEnvelope = Pareto { unPa :: RBTree PPoint } deriving (Show,Eq)

emptyEnvelope = Pareto empty

readInput    :: [T.Text] -> [PointSet3]
readInput [] = []
readInput (ns:xs) = let n = readInt ns
                        (pss,rest) = L.splitAt n xs
                    in map readPoint pss : readInput rest

readInt t = case TR.decimal t of
              Right (x,_) -> x


readPoint   :: T.Text -> Point3
readPoint s = let [r1,r2,r3] = map readInt . T.words $ s in (r1,r2,r3)

thd (_,_,c) = c

shortListSize :: [Point3] -> Int
shortListSize = snd . L.foldl' f (emptyEnvelope,0) . L.sortBy (comparing thd)
  where
    f (e,c) (r1,r2,_) = case insert (r1,r2) e of
                          Nothing -> (e,c)
                          Just e' -> (e',c+1)

insert :: Point2 -> ParetoEnvelope -> Maybe ParetoEnvelope
-- insert p (Pareto e) | traceShow (p,toList e) False = undefined
insert p e
  | (PPoint p) `aboveEnvelope` e = Nothing
  | otherwise                    = Just $ insert' (PPoint p) e


-- insert the new point in the pareto envelope. This (may replace) a piece in
-- the middle of the envelope.
insert' :: PPoint -> ParetoEnvelope -> ParetoEnvelope
insert' p@(PPoint (_,y)) (Pareto e) =
  let
    -- e' is not dominated. So we have to keep it
    (e',es) = split p e
              -- The pareto envelope is also y-monotonic. So we can easily
              -- find all points that are below p. These points are not dominated
              -- so we have to keep them in the envelope
    mqq = findMonotonic (\(PPoint (qx,qy)) -> qy < y) es
    e'' = case mqq of
            Top   -> empty
            Val q -> insertRB q . snd $ split q es -- R.split deletes q, so we have to reinsert it
  in Pareto $ join e' p e''

-- | Similar to option, but ordered such that Top represents infinity in the ordering
data Option a = Val a | Top deriving (Show,Eq,Ord)

-- | Given a monotonic predicate. Find the smallest value x such that p x = True.
findMonotonic :: Ord a => (a -> Bool) -> RBTree a -> Option a
findMonotonic _ Leaf = Top
findMonotonic p (Node _ _ l m r)
  | p m       = findMonotonic p l `min` Val m
  | otherwise = findMonotonic p r


(PPoint (px,py)) `dominates` (PPoint (qx,qy)) = px <= qx && py <= qy

aboveEnvelope :: PPoint -> ParetoEnvelope -> Bool
aboveEnvelope _ (Pareto Leaf) = False
aboveEnvelope p (Pareto (Node _ _ l m r))
  | m `dominates` p = True
  | p < m           = aboveEnvelope p $ Pareto l
  | m < p           = aboveEnvelope p $ Pareto r
  | otherwise       = error $ "aboveEnvelope: this should not happen " ++ show (p,m)

--------------------------------------------------------------------------------

-- Red black trees
data Color = Red | Black deriving (Show,Eq)
type BlackHeight = Int

data RBTree a = Leaf | Node !Color !BlackHeight !(RBTree a) a !(RBTree a) deriving (Show,Eq)

empty = Leaf

blacken (Node Red h l x r) = Node Black (h+1) l x r
blacken n                  = n


blackHeight Leaf             = 0
blackHeight (Node _ h _ _ _) = h

insertRB x = blacken . insertRB' x

insertRB' :: Ord a => a -> RBTree a -> RBTree a
insertRB' x Leaf = Node Red 0 Leaf x Leaf
insertRB' x (Node c h l y r)
  | x <= y    = balance c h (insertRB' x l) y r
  | otherwise = balance c h l y (insertRB' x r)


split :: Ord a => a -> RBTree a -> (RBTree a, RBTree a)
split x t = let (l,r) = split' x t in (blacken l, blacken r)

split' :: Ord a => a -> RBTree a -> (RBTree a, RBTree a)
split' x Leaf = (Leaf,Leaf)
split' x (Node c h l y r)
  | x == y    = (l,r)
  | x <  y    = let (ll,lr) = split' x l in (ll,join lr y r)
  | otherwise = let (rl,rr) = split' x r in (join l y rl,rr)

join :: Ord a => RBTree a -> a -> RBTree a -> RBTree a
join l m r
  | blackHeight l >= blackHeight r = joinL l m r
  | otherwise                      = joinR l m r

-- pre: Blackheight left >= blackHeight r
joinL Leaf               m rr = balance Red 0 Leaf m rr
joinL n@(Node c h l x r) m rr
  | h == blackHeight rr = balance Red h n m rr
  | otherwise           = balance c   h l x (joinL r m rr)

joinR ll  m Leaf = balance Red 0 ll m Leaf
joinR ll m n@(Node c h l x r)
  | h == blackHeight ll = balance Red h ll             m n
  | otherwise           = balance c   h (joinR ll m l) x r


balance  :: Color -> BlackHeight -> RBTree a -> a -> RBTree a -> RBTree a
balance Black h (Node Red _ (Node Red _ a x b) y c) z d = node h a x b y c z d
balance Black h (Node Red _ a x (Node Red _ b y c)) z d = node h a x b y c z d
balance Black h a x (Node Red _ (Node Red _ b y c) z d) = node h a x b y c z d
balance Black h a x (Node Red _ b y (Node Red _ c z d)) = node h a x b y c z d
balance co h a x b = Node co h a x b

node h a x b y c z d = Node Red h (Node Black h a x b) y (Node Black h c z d)

toList Leaf = []
toList (Node _ _ l x r) = toList l ++ x : toList r

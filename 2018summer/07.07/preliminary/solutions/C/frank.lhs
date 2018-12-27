---
title: Floor Painting with a Sweep line
author: Frank Staals
---

@EXPECTED_RESULTS@: TIMELIMIT

$O(n^2 \log^2 n)$ time.

> {-# LANGUAGE DataKinds #-}
> {-# LANGUAGE KindSignatures #-}
> {-# LANGUAGE TypeFamilies #-}
> {-# LANGUAGE FlexibleContexts #-}
> {-# LANGUAGE GeneralizedNewtypeDeriving #-}
> {-# LANGUAGE DeriveFunctor #-}
> {-# LANGUAGE MultiParamTypeClasses #-}
> {-# LANGUAGE TypeOperators #-}
> {-# LANGUAGE FunctionalDependencies #-}
> {-# LANGUAGE FlexibleInstances #-}
> module Main where


> import Prelude hiding (foldr)
> import Control.Applicative((<$>))
> import Data.Foldable(toList,Foldable(..))
> import Data.Ord(comparing)
> import Data.Monoid
> import Data.Maybe
> import Data.Either
> import qualified Data.List     as L
> import qualified Data.Vector as V

> import Debug.Trace


-- > maxSquareWidth   :: RectPolygon -> Width
-- > maxSquareWidth p = undefined


> maxSquareWidth   :: RectPolygon -> Width
> maxSquareWidth p = max (maxHorizontalSquareWidth p)
>                        (maxHorizontalSquareWidth $ rotate p)


> maxHorizontalSquareWidth :: RectPolygon -> Width
> maxHorizontalSquareWidth p@(RectPolygon (Sorted hs) _) =
>     fst . foldr handleSegment (0,Hist dummy) $ hs

> dummy :: BalBST Key (Interval Int)
> dummy = singleton (Interval Nothing minBound maxBound)


for forward segments (top segments) there is no need to check if we can fit something

for backward segments (bottom segments) we first check the maximum width that
fits and then insert the new bottom segment.

> handleSegment :: Segment Horizontal -> (Width,SHist) -> (Width,SHist)
> -- handleSegment s (maxW,h) | traceShow s False = undefined
> handleSegment s (maxW,h)
>   | isForward s = (maxW,       insertSegment s h)
>   | otherwise   = (max maxW w, insertSegment s h)
>   where
> --    w  = traceShow (s,w') w'
>     w = maxHeightAt (elevation s) h


> data Range a = Range a a deriving (Show,Eq,Ord)
>
> type XCoord = Int
> type YCoord = Int
> data Key = Key { key   :: XCoord
>                , minY  :: Maybe YCoord -- Nothing = -infty
>                , range :: Range XCoord
>                }
>          deriving (Show,Eq,Ord)



> instance IsKey Key where
>   (Key _ y (Range l m)) .<>. (Key _ y' (Range _ r)) = Key m (min y y') (Range l r)


> data Interval a = Interval { yCoord  :: Maybe a
>                            , left'   :: a
>                            , right'  :: a
>                            }
>                 deriving (Show,Eq)


> instance Key `IsKeyFor` (Interval Int) where
>   toKey (Interval y l r) = Key l y (Range l r)
>   goLeft (Interval _ l _) (Key k _ _) = l < k


> newtype Hist a = Hist { unH :: BalBST Key a }
>                deriving (Show,Eq)


> type SHist = Hist (Interval Int)
> type WHist = Hist Width

> shist :: SHist
> shist = foldr insertSegment (Hist dummy) myHs

> insertSegment :: Segment Horizontal -> SHist -> SHist
> insertSegment seg@(Segment y' s e) (Hist t) = Hist $ replace i t
>   where
>     (l,r)    = (min s e, max s e)
>     y        = if isForward seg then Just y' else Nothing
>     --bottom segments are backwards, top segments forward.
>     -- so the height after bottom segments is -infty
>     i        = Interval y l r


> mkInt :: Int -> Int -> Interval Int
> mkInt = Interval Nothing


--> ints = fromSortedList [mkInt 0 1, mkInt 1 3, mkInt 3 10, mkInt 10 20]


> replace i@(Interval _ l r) t = lt `join` m `join` rt
>   where
>     (lt,j@(Interval lh ll lr), rt') = split (mkInt l l) t
>     (_, Interval rh rl rr, rt)      = split (mkInt r r) (singleton j `join` rt')
>     li         = if ll < l  then Just (Interval lh ll l) else Nothing
>     ri         = if r  < rr then Just (Interval rh r rr) else Nothing
>     m          = fromSortedList . catMaybes $ [ li, Just i, ri ]


> type Height = Int

O(n \log^2 n)

> maxHeightAt                 :: YCoord -> SHist -> Height
> --maxHeightAt y hist | traceShow (y,hist) False = undefined
> maxHeightAt _ (Hist Empty) = 0
> maxHeightAt y hist@(Hist t) = maximumA hs
>   where
>     hs     = fmap (\i -> maxWidthAt y (left' i) rights hist) $ ints
>     ints   = listArray . toList $ t
>     rights = fmap right' ints


$O(\log^2 n)$

> maxWidthAt                 :: YCoord -> XCoord -> Array XCoord -> SHist -> Width
> -- maxWidthAt y l r h | traceShow (y,l,r,h) False = undefined
> maxWidthAt y l rights hist = maybe 0 (subtract l) . safeLastA $ rs
>   where
>     (rs,_)      = spanMonotonic (not . rightFits) rights
>     rightFits r
>       | l >=   r  = True
>       | otherwise = heightIn y l r hist >= (r - l)
>                   -- test if the height is at least the width, and thus fits.

$O(\log n)$

given the current height y, a left and right boundary. Get the smallest height
h in the hist whtin left and right. I.e. The largest square in this range can
have height at most h

> heightIn                :: YCoord -> XCoord -> XCoord -> SHist -> Height
> heightIn y l r (Hist t) = maybe 0 (subtract y) $ minY =<< getKey t''
>   where
>     (_,t')  = split' l t
>     (t'',_) = split' r t'



> testT' = unH $ foldr insertSegment (Hist . singleton $ mkInt minBound maxBound)
>          $ horizontalEdges testPoly1

> testT = fromSortedList [mkInt 0 192, Interval (Just 704) 192 256, Interval (Just 650) 256 320,mkInt 320 10000]



> split' x t = (lt,singleton lf `join` rt)
>   where
>     (lt,lf,rt) = split (Interval Nothing x x) t



$O(\log n)$ time

> spanMonotonic :: (a -> Bool)   -> Array a
>               -> (Array a, Array a)
> spanMonotonic p s
>   | nullA s             = (s,s)
>   |       p . headA $ s = (listArray [],s)
>   | not . p . lastA $ s = (s, listArray [])
>   | otherwise           = let i = binarySearch (p . (s !)) 0 (size s - 1)
>                           in splitAtA i s

Given a monotonic predicate p, a lower bound l, and an upper bound u, with p l
= False, p u = True, and l < u. Get the index h such that everything strictly smaller than
h has: p i = False, and all i >= h, we have p h = True

> binarySearch       :: Integral a => (a -> Bool) -> a -> a -> a
> binarySearch p l u = let d = u - l
>                          m = l + (d `div` 2)
>                      in if d == 1 then u else
>                           if p m then binarySearch p l m
>                                  else binarySearch p m u



Balanced Binary Search Tree
---------------------------

> class IsKey k where
>   (.<>.) :: k -> k -> k

> class IsKey k => k `IsKeyFor` v | v -> k where
>   toKey :: v -> k

>   goLeft :: v -> k -> Bool
>   goLeft x k = not $ goRight x k
>   goRight :: v -> k -> Bool
>   goRight x k = not $ goLeft x k

--------------------------------------------------------------------------------
-

> fromSortedList :: (k `IsKeyFor` v) => [v] -> BalBST k v
> fromSortedList = foldr (\x t -> singleton x `join` t) Empty


> data BalBST k v = Empty | BalBST (Node k v)
>                deriving (Show,Eq)

> data Color = Red | Black deriving (Show,Eq)

> type BlackHeight = Int

> data Node k v = Leaf v
>               | Node Color !(Node k v) BlackHeight k !(Node k v)
>               deriving (Show,Eq)


> instance Foldable (Node k) where
>   foldMap f (Leaf v) = f v
>   foldMap f (Node _ l _ _ r) = foldMap f l <> foldMap f r
> instance Foldable (BalBST k) where
>   foldMap _ Empty = mempty
>   foldMap f (BalBST n) = foldMap f n



> getKey Empty                     = Nothing
> getKey (BalBST (Leaf x))         = Just $ toKey x
> getKey (BalBST (Node _ _ _ k _)) = Just k


> blackHeight :: Node k v -> BlackHeight
> blackHeight (Leaf _) = 0
> blackHeight (Node _ _ h _ _ ) = h
>
> balBST :: Node k v -> BalBST k v
> balBST n@(Leaf _) = BalBST n
> balBST n          = BalBST . blacken $ n
>
> blacken :: Node k v -> Node k v
> blacken (Node c l h k r) = let h' = if c == Black then h else h + 1
>                            in Node Black l h' k r

> empty = Empty
> singleton x = BalBST (Leaf x)

-- pre: max left <= min right

> join :: (k `IsKeyFor` v) => BalBST k v -> BalBST k v -> BalBST k v
> Empty        `join` r = r
> l@(BalBST _) `join` Empty = l
> (BalBST l)   `join` (BalBST r) = balBST $ l `joinN` r

> joinN :: (k `IsKeyFor` v) => Node k v -> Node k v -> Node k v
> l `joinN` r
>   | blackHeight l <= blackHeight r = joinNodeR l r
>   | otherwise                      = joinNodeL l r



-- pre: - blackHeight Left >= blackHeight Right
--      - max left <= min right

> joinNodeL :: (k `IsKeyFor` v) => Node k v -> Node k v -> Node k v
> joinNodeL l@(Leaf _) r           = balance Red   l  0 r
>   -- if l is a leaf, the blackheight of r must be 0 as well, and thus we attach here
> joinNodeL l@(Node Black lc  h _ rc) r
>   | h == blackHeight r           = balance Red   l  h r
>   | otherwise                    = balance Black lc h (joinNodeL rc r)
> joinNodeL (Node Red lc h _ rc) r = balance Red   lc h (joinNodeL rc r)
>

-- pre: - blackHeight Left <= blackHeight Right
--      - max left <= min right
 
> joinNodeR :: (k `IsKeyFor` v) => Node k v -> Node k v -> Node k v
> joinNodeR l r@(Leaf _)             = balance Red   l 0 r
>   -- if l is a leaf, the blackheight of r must be 0 as well, and thus we attach here
> joinNodeR l r@(Node Black lc  h _ rc)
>   | h == blackHeight l           = balance Red   l  h r
>   | otherwise                    = balance Black (joinNodeR l lc) h rc
> joinNodeR l (Node Red lc h _ rc) = balance Red   (joinNodeR l lc) h rc





> balance :: (k `IsKeyFor` v) => Color -> Node k v -> BlackHeight -> Node k v -> Node k v
> balance Black (Node Red (Node Red a _ _ b) _ _ c) h d = bal h a b c d
> balance Black (Node Red a _ _ (Node Red b _ _ c)) h d = bal h a b c d

> balance Black a h (Node Red b _ _ (Node Red c _ _ d)) = bal h a b c d
> balance Black a h (Node Red (Node Red b _ _ c) _ _ d) = bal h a b c d
> balance c     l h r                                   = node c l h r


> bal :: (k `IsKeyFor` v)
>        => BlackHeight -> Node k v -> Node k v -> Node k v -> Node k v -> Node k v
> bal h a b c d = node Red (node Black a h b) h (node Black c h d)


> node :: (k `IsKeyFor` v) => Color -> Node k v -> BlackHeight -> Node k v -> Node k v
> node c l h r = Node c l h (l <..> r) r
>   where
>     (Leaf x)         <..> (Leaf y)         = toKey x .<>. toKey y
>     (Leaf x)         <..> (Node _ _ _ k _) = toKey x .<>. k
>     (Node _ _ _ k _) <..> (Leaf x)         = k .<>. toKey x
>     (Node _ _ _ k _) <..> (Node _ _ _ z _) = k .<>. z

--------------------------------------------------------------------------------

-- Given a tree t with elements v_1,..,v_k,x,v_{k+2},..,v_n into a tree for
-- v_1,..,v_k, the element x, and a tree for elements v_{k+2}, v_n.

> split :: (k `IsKeyFor` v) => v -> BalBST k v -> (BalBST k v, v, BalBST k v)
> split _ Empty = error "split: on empty tree"
> split x (BalBST n) = splitNode x n

-- More specifically. SplitNode finds the leaf y that searching for x guides us
-- to, and returns this y.

> splitNode :: (k `IsKeyFor` v) => v -> Node k v -> (BalBST k v, v, BalBST k v)
> splitNode _ (Leaf y) = (Empty, y, Empty)
> splitNode x (Node _ l _ k r)
>   | goLeft x k = let (l',m,r') = splitNode x l in (l', m, r' `join` BalBST r)
>   | otherwise  = let (l',m,r') = splitNode x r in (BalBST l `join` l', m, r')





> delete :: (Eq v, k `IsKeyFor` v) => v -> BalBST k v -> BalBST k v
> delete x t = let (l,y,r) = split x t in
>              if x == y then l `join` r else t

> deleteUnSafe     :: (k `IsKeyFor` v) => v -> BalBST k v -> BalBST k v
> deleteUnSafe x t = let (l,_,r) = split x t in l `join` r


> insert :: IsKeyFor k v => v -> BalBST k v -> BalBST k v
> insert x t = l `join` m `join` r
>   where
>     (l,y,r) = split x t
>     m       = if goLeft x (toKey x .<>. toKey y) then singleton x `join` singleton y
>                                                  else singleton y `join` singleton x

Preliminaries
-------------

We start with the following observation:

<div class="observation">
Let $P$ be a rectilinear polygon, and let $S$ be a square such that $\partial
P$ intersects $\partial S$. There are edges $e_S \in \partial S$ and $e_P \in
\partial P$ such that $e_S$ and $e_P$ are of a different orientation.
</div>

Hence, we only have to wory about edges (segments) of different orientations
intersecting each other. We define this as follows:

> data Orientation = Horizontal | Vertical

> type family Other (o :: Orientation) :: Orientation
> type instance Other Horizontal = Vertical
> type instance Other Vertical   = Horizontal

All our segments have an orientation. Since they are given in clockwise order,
all segments will have the interior of the polygon to their right. We refer to
the coordinate that the end points share as the *elevation* of the segment. We
then arrive at the folowing data type defining a segment.

> data Segment (o :: Orientation) = Segment { elevation :: Int
>                                           , start     :: Int
>                                           , end       :: Int
>                                           }
>                                   deriving (Show,Eq)

Note that since segments are oriented to have the polygon to their right, the
"start" value may be larger than the "end" value.

We can then define a function that checks if two segments, of different
orientations, *properly* intersect. That is, if the interiors of the line
segments intersect. In technical terms, the *closed* segment $\overline{pq}$
intersects the *closed* segment $\overline{rs}$.

> intersects                         :: Segment o -> Segment (Other o) -> Bool
> (Segment e p q) `intersects` (Segment f r s) = f `inClosedRange` (p,q)
>                                                &&
>                                                e `inClosedRange` (r,s)
>

> inOpenRange :: Ord a => a -> (a,a) -> Bool
> a `inOpenRange` r = inRangeWith (<) a r

> inClosedRange:: Ord a => a -> (a,a) -> Bool
> a `inClosedRange` r = inRangeWith (<=) a r

> inRangeWith      :: Ord a => (a -> a -> Bool) -> a -> (a,a) -> Bool
> inRangeWith (<:)  a (b,c) = (min b c) <: a && a <: (max b c)

For a Rectilinear polygon we store the horizontal and vertical edges
separately. We store these sets in arrays, so we have $O(1)$ access to an
element, given its index. The segments are stored ordered by their
elevation. We use the `Sorted` type as a tag, to remind us of this.

> data RectPolygon = RectPolygon {
>                      horizontalEdges :: Sorted Array (Segment Horizontal)
>                    , verticalEdges   :: Sorted Array (Segment Vertical)
>                    }
>                    deriving (Show)
>
> newtype Sorted s a = Sorted { unS :: s a }
>                      deriving (Show,Eq,Ord,Read,Functor,Foldable)

A square in is stored terms of `Segement`s as well.

> data Square = Square { top    :: Segment Horizontal
>                      , right  :: Segment Vertical
>                      , bottom :: Segment Horizontal
>                      , left   :: Segment Vertical
>                      }
>               deriving (Show,Eq)
>
> trbl :: Square -> (Int,Int,Int,Int)
> trbl (Square t _ _ l) = (end l, end t, start l, start t)

Furthermore, we provide some convencience functions for working with
squares. In particular, the function `square` to construct a square, given the
topleft `Point` and the bottom right `Point`, And functions to retrieve the
horizontal and vertical sides of the square.

> newtype Point = Point { unP :: (Int,Int) } deriving (Show,Eq)
> getX = fst . unP
> getY = snd . unP
>
> square                                 :: Point -> Point -> Square
> square (Point (px,py)) (Point (qx,qy)) = Square (Segment py px qx)
>                                                 (Segment qx py qy)
>                                                 (Segment qy qx px)
>                                                 (Segment px qy py)
>
> horizontalSides                  :: Square -> [Segment Horizontal]
> horizontalSides (Square t _ b _) = [t,b]
>
> verticalSides                  :: Square -> [Segment Vertical]
> verticalSides (Square _ l _ r) = [l,r]

Finally, we define some more convenience functions on `Segment`s. As these
functions depend on the orientation, we implement them in a typeclass.

> class Properties (o :: Orientation) where
>   startPoint        :: Segment o -> Point
>   endPoint          :: Segment o -> Point
>   intersectionPoint :: Segment o -> Segment (Other o) -> Point


The purpose of the these four functions should be self-explanatory. As should
their implementations:

> instance Properties Horizontal where
>   startPoint s = Point (start s, elevation s)
>   endPoint   s = Point (end s,   elevation s)
>   intersectionPoint s s' = Point (elevation s', elevation s)
>
> instance Properties Vertical where
>   startPoint s = Point (elevation s, start s)
>   endPoint   s = Point (elevation s, end s)
>   intersectionPoint s s' = Point (elevation s, elevation s')


> type Width = Int


> shift :: RectPolygon -> RectPolygon
> shift (RectPolygon hs vs) = RectPolygon hs' vs'
>   where
>     dy = abs . min 0 . minimum . map elevation . toList $ hs
>     hs' = fmap (\s -> s { elevation = dy + elevation s } ) hs
>     vs' = fmap (\s -> s { start     = dy + start s
>                         , end       = dy + end s }) vs

> rotate :: RectPolygon -> RectPolygon
> rotate (RectPolygon hs vs) = RectPolygon vs' hs'
>   where
>     vs' = Sorted . reverseA . fmap rotateSegment . unS $ vs
>     hs' = Sorted . reverseA . fmap rotateSegment . unS $ hs

> rotateSegment                 :: Segment o -> Segment (Other o)
> rotateSegment (Segment e s t) = Segment (-e) s t

> isForward                 :: Segment o -> Bool
> isForward (Segment _ p q) = p < q


Reading Input
------------


> readInput           :: [String] -> [RectPolygon]
> readInput []        = []
> readInput (ns:rest) = let n       = read ns
>                           (xs,ys) = L.splitAt n rest
>                       in readPolygon xs : readInput ys

> readPolygon    :: [String] -> RectPolygon
> readPolygon ss = RectPolygon (sorted $ lefts segs) (sorted $ rights segs)
>   where
>     vertices = map readVertex ss
>     segs     = zipWith toSegment vertices (tail vertices ++ vertices)
>
>     sorted :: [Segment o] -> Sorted Array (Segment o)
>     sorted = Sorted . listArray . toList . L.sortBy (comparing elevation)

-->     sortByElev = S.unstableSortBy (compare `on` elevation)


> readVertex   :: String -> Point
> readVertex s = let [x,y] = map read . words $ s
>                in Point (x,y)

> toSegment :: Point -> Point -> Either (Segment Horizontal) (Segment Vertical)
> toSegment (Point (px,py)) (Point (qx,qy))
>   | py == qy  = Left  $ Segment py px qx
>   | otherwise = Right $ Segment px py qy


> main :: IO ()
> main = interact $
>          unlines . map (show . maxSquareWidth) . readInput . tail . lines

Version that reads from file instead of stdin

> mainF = readFile "testdata.in"
>         >>= putStr . unlines . map (show . maxSquareWidth) . readInput . tail . lines

Some Array Primitives
----------------------

We need $O(1)$ reverses. So, implement a wrapper around Vector

> data Array a = Forward (V.Vector a)
>              | Reverse (V.Vector a)
>              deriving (Show,Eq,Ord,Functor)

> instance Foldable Array where
>   foldMap f (Forward v) = foldMap f v
>   foldMap f (Reverse v) = foldr (\x m -> m <> f x) mempty v
>                           -- note that we have m on the left and f x on the right!


> rawVec (Forward v) = v
> rawVec (Reverse v) = v

> size :: Array a -> Int
> size = V.length . rawVec

> nullA :: Array a -> Bool
> nullA = V.null  . rawVec

> elems             :: Array a -> [a]
> elems (Forward v) = V.toList v
> elems (Reverse v) = reverse . V.toList $ v

> (!) :: Array a -> Int -> a
> (Forward v) ! i = v V.! i
> (Reverse v) ! i = v V.! (V.length v - 1 - i)

> listArray :: [a] -> Array a
> listArray = Forward . V.fromList

> splitAtA               :: Int -> Array a -> (Array a, Array a)
> splitAtA i (Forward v) = let (v1,v2) = V.splitAt i v in (Forward v1, Forward v2)
> splitAtA i (Reverse v) = let j = V.length v - i
>                              (v2,v1) = V.splitAt j v in (Reverse v1, Reverse v2)

> headA, lastA :: Array a -> a
> headA a = a ! 0
> lastA a = a ! (size a - 1)

> safeLastA :: Array a -> Maybe a
> safeLastA a
>   | size a == 0 = Nothing
>   | otherwise   = Just $ lastA a

> reverseA             :: Array a -> Array a
> reverseA (Forward v) = Reverse v
> reverseA (Reverse v) = Forward v

> maximumA = V.maximum . rawVec


--------------------------------------------------------------------------------


> testPoly = readPolygon . lines

> testPoint = Point (192,704)

> testPoly1 = testPoly "192 704\n256 704\n256 640\n320 640\n320 592\n192 592\n"


> myHs = elems . unS . horizontalEdges $ testPoly1

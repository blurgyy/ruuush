-- @EXPECTED_RESULTS@: CORRECT

-- Maze with mutable array + array-size tracking during the simulation.

module Main where

import           Control.Applicative
import           Control.Monad
import           Control.Monad.State
import           Data.List
import           Data.Maybe
import           Data.Monoid

import           Control.Monad.ST

import           Data.Vector(Vector,toList)
import qualified Data.Vector as V
import qualified Data.Vector.Mutable as MV
import           Data.Vector.Mutable(STVector,MVector)


main = interact $ unlines . withTail (map (show . trunc . simulate) . readInput) . lines
       where
         withTail f (x:xs) = x : f xs


data Field = Free | Wall deriving (Eq)

instance Show Field where
  show Free = "."
  show Wall = "#"

data Action = F | L | R | B deriving (Show,Read,Eq,Ord)

type Row = Vector Field
newtype Maze = Maze { unM :: Vector Row } deriving (Eq)

type Path = [Action]

readInput :: [String] -> [Path]
readInput = map (map read')
  where
    read' 'F' = F
    read' 'L' = L
    read' 'R' = R
    read' 'B' = B

maxSize = 100

type Position = (Int,Int)

instance Show Maze where
  show m@(Maze rs) = let (h,w) = size m
                         ss    = unwords . map show $ [h,w]
                     in
                     intercalate "\n" . (ss :) . map showRow . toList $ rs

size (Maze vs) = (V.length vs , V.length . V.head $ vs)


showRow = concatMap show . toList

trunc           :: Maze -> Maze
trunc = id

lastFree   :: Vector Field -> Maybe Int
lastFree v = let vi = V.findIndices (== Free) v
             in if V.null vi then Nothing else Just $ V.last vi


slice'     :: Int -> Int -> Vector a -> Vector a
slice' s e = let l = e - s in V.slice s l

data Orientation = East | South | West | North deriving (Show,Eq,Ord,Enum)


type STMaze s = STVector s (STVector s Field)

type State' s = StateT (Position,Orientation,STMaze s,SizeInfo) (ST s)


newtype Min a = Min {unMin :: a} deriving (Show,Eq,Ord)
newtype Max a = Max {unMax :: a} deriving (Show,Eq,Ord)

instance Ord a => Monoid (Min a) where
  (Min a) `mappend` (Min b) = Min $ a `min` b
instance Ord a => Monoid (Max a) where
  (Max a) `mappend` (Max b) = Max $ a `max` b



newtype SizeInfo = SizeInfo (Min Int, Max Int, Max Int)

instance Monoid SizeInfo where
  (SizeInfo a) `mappend` (SizeInfo b) = SizeInfo (a <> b)

sizeInfo (r,c) = SizeInfo (Min r, Max r, Max c)



initialMaze :: ST s (STMaze s)
initialMaze = let initRow = MV.replicate maxSize Wall in
              MV.replicateM (2*maxSize) initRow


-- initialMaze :: STMaze s
-- initialMaze = let initRow = V.replicate maxSize Wall in
--               Maze $ V.replicate (2*maxSize) initRow


simulate   :: Path -> Maze
simulate p = runST $ do
               m <- initialMaze
               (_,_,_,si) <- execStateT (simulate' p) (start,East,m,sizeInfo start)
               let SizeInfo (Min sr, Max er, Max c) = si
                   rows = [(sr-1)..(er +1)]
               Maze . V.fromList <$> mapM (create m $ c + 2) rows
  where
    create m c i = MV.read m i >>= V.unsafeFreeze . MV.slice 0 c

 -- evalState (simulate' p) (start,East,initialMaze)


simulate'   :: Path -> State' s ()
simulate' p = mapM_ simA p


free             :: (Position,Orientation,STMaze s,SizeInfo) -> ST s ()
free ((r,c),_,m,_) = do
  rr <- MV.read m r
  MV.write rr c Free


visit :: State' s ()
visit = modify updateSizeInfo >> get >>= lift . free
  where
    updateSizeInfo (p,o,m,si) = (p,o,m,sizeInfo p <> si)


simA :: Action -> State' s ()
simA a = visit >> nextPos a

nextOrient o     F = o
nextOrient o     R = succ' o
nextOrient o     L = pred' o
nextOrient o     B = pred' $ pred' o

succ' North = East
succ' o     = succ o

pred' East = North
pred' o    = pred o


advance East  (r,c)  = (r,c+1)
advance South (r,c) = (r+1,c)
advance West  (r,c)  = (r,c-1)
advance North (r,c) = (r-1,c)

nextPos'         :: Action -> (Position,Orientation) -> (Position,Orientation)
nextPos' a (p,o) = let o' = nextOrient o a in (advance o' p, o')

nextPos :: Action -> State' s ()
nextPos a = modify $ \(p,o,m,si) -> let (p',o') = nextPos' a (p,o) in (p',o',m,si)

-- we start in the middle row on the leftmost position
start = (maxSize,0)

-- simulate :: Path -> Maze
-- simulate = Maze . V.create . simulate'

-- simulate'   :: Path -> ST STMaze
-- simulate' p = do
--                 m <- initialMaze
--                 simulate'' m p
--                 snd <$> get



-- simA     :: State' -> Action -> ST State'
-- simA s a =

-- type State'   = (Position,Orientation)
-- type STMaze = STVector State' (STVector State' Field)

-- initialMaze :: ST STMaze
-- initialMaze = let initRow = V.replicate maxSize Wall in
--               Maze <$> V.replicateM (2*maxSize) initRow

-- visit :: Position -> ST ()
-- visit = undefined

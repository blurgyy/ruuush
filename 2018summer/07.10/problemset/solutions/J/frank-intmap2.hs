-- @EXPECTED_RESULTS@: CORRECT

module Main where

-- We start with a maze that is too large, we simulate traversing the path and
-- then trunicate the max to the correct size.

-- Maze with immutable Intmaps instead of arrays/vectors + trunication as a separate step.

import           Control.Applicative
import           Control.Monad
import           Control.Monad.State
import qualified Data.Foldable as F
import qualified Data.IntMap as I
import           Data.IntMap(IntMap)
import           Data.List
import           Data.Maybe

main = interact $ unlines . withTail (map (show . trunc . simulate) . readInput) . lines
       where
         withTail f (x:xs) = x : f xs


data Field = Free | Wall deriving (Eq)

instance Show Field where
  show Free = "."
  show Wall = "#"

data Action = F | L | R | B deriving (Show,Read,Eq,Ord)

type Row = IntMap Field
newtype Maze = Maze { unM :: IntMap Row } deriving (Eq)

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
                     intercalate "\n" . (ss :) . map showRow . I.elems $ rs

showRow = concatMap show . I.elems

head' = snd . I.findMin
last' = snd . I.findMax

size :: Maze -> (Int, Int)
size (Maze vs) = (I.size vs , I.size . head' $ vs)


take' :: Int -> IntMap a -> IntMap a
take' k = I.fromDistinctAscList . take k . I.toAscList

trunc           :: Maze -> Maze
trunc (Maze rs) = Maze $ fmap (take' width) rs'
  where
    allWall       = F.all (== Wall)
    ix            = I.filter (not . allWall) rs
    (startR,endR) = (fst (I.findMin ix) - 2, 2 + fst (I.findMax ix))

    rs'   = slice' startR endR rs
    width = 2 + (fromMaybe 3 . F.maximum $ fmap lastFree rs')


lastFree :: IntMap Field -> Maybe I.Key
lastFree = fmap (fst . fst) . I.maxViewWithKey . I.filter (== Free)

slice' :: Int -> I.Key -> IntMap a -> IntMap a
slice' s e m = let (_,m') = I.split s m in fst $ I.split e m'

data Orientation = East | South | West | North deriving (Show,Eq,Ord,Enum)

type State' = State (Position,Orientation,Maze)


fromList' :: [a] -> IntMap a
fromList' = I.fromDistinctAscList . zip [0..]


initialMaze :: Maze
initialMaze = let initRow = fromList' $ replicate maxSize Wall in
              Maze . fromList' $ replicate (2*maxSize) initRow


simulate   :: Path -> Maze
simulate p = evalState (simulate' p) (start,East,initialMaze)

simulate'   :: Path -> State' Maze
simulate' p = mapM_ simA p >> ((\(_,_,m) -> m) <$> get)


free :: Position -> Maze -> Maze
free (r,c) (Maze m) = Maze $ I.adjust f r m
  where
    f = I.adjust (const Free) c

visit :: State' ()
visit = modify $ \(p,o,m) -> (p,o,free p m)

simA :: Action -> State' ()
simA a = visit >> nextPos a

nextOrient o     F = o
nextOrient o     R = succ' o
nextOrient o     L = pred' o
nextOrient o     B = pred' $ pred' o


-- cyclic successor and predecessor
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

nextPos :: Action -> State' ()
nextPos a = modify $ \(p,o,m) -> let (p',o') = nextPos' a (p,o) in (p',o',m)

-- we start in the middle row on the leftmost position
start = (maxSize,0)

-- @EXPECTED_RESULTS@: TIMELIMIT

-- First version. Most idiomatic haskell + using immutable vectors (which is
-- performance wise not a good idea).
module Main where

import Data.Maybe
import Data.List
import           Control.Applicative
import           Control.Monad
import Control.Monad.State
import Data.Vector(Vector,toList)
import qualified  Data.Vector as V

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
trunc (Maze rs) = Maze $ fmap (V.take width) rs'
  where
    allWall       = V.all (== Wall)
    ix            = V.findIndices (not . allWall) rs
    (startR,endR) = (V.head ix - 1, 2 + V.last ix)

    rs'  :: Vector (Vector Field)
    rs'   = slice' startR endR rs
    width = 2 + (fromMaybe 3 . V.maximum $ fmap lastFree rs')

lastFree   :: Vector Field -> Maybe Int
lastFree v = let vi = V.findIndices (== Free) v
             in if V.null vi then Nothing else Just $ V.last vi


slice'     :: Int -> Int -> Vector a -> Vector a
slice' s e = let l = e - s in V.slice s l

data Orientation = East | South | West | North deriving (Show,Eq,Ord,Enum)

type State' = State (Position,Orientation,Maze)


initialMaze :: Maze
initialMaze = let initRow = V.replicate maxSize Wall in
              Maze $ V.replicate (2*maxSize) initRow


simulate   :: Path -> Maze
simulate p = evalState (simulate' p) (start,East,initialMaze)

simulate'   :: Path -> State' Maze
simulate' p = mapM_ simA p >> ((\(_,_,m) -> m) <$> get)


free :: Position -> Maze -> Maze
free (r,c) (Maze m) = let rr  = m V.! r
                          rr' = rr V.// [(c,Free)]
                      in Maze $ m V.// [(r,rr')]

visit :: State' ()
visit = modify $ \(p,o,m) -> (p,o,free p m)

simA :: Action -> State' ()
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

nextPos :: Action -> State' ()
nextPos a = modify $ \(p,o,m) -> let (p',o') = nextPos' a (p,o) in (p',o',m)

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

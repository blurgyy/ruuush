-- @EXPECTED_RESULTS@: TIMELIMIT

-- This version is identical to frank-intmap2 with the exception of reading the
-- input. Since read is seriously broken performance-wise, this version is
-- significiantly slower.

module Main where

import Data.Maybe
import Data.List
import           Control.Applicative
import           Control.Monad
import Control.Monad.State
import qualified Data.Foldable as F
import Data.IntMap(IntMap,toList)
import qualified Data.IntMap as I


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
readInput = map (map (read . (:[])))

maxSize = 100

type Position = (Int,Int)

instance Show Maze where
  show m@(Maze rs) = let (h,w) = size m
                         ss    = unwords . map show $ [h,w]
                     in
                     intercalate "\n" . (ss :) . map showRow . I.elems $ rs

head' = snd . I.findMin
last' = snd . I.findMax

size (Maze vs) = (I.size vs , I.size . head' $ vs)


showRow = concatMap show . I.elems

take' k = I.fromDistinctAscList . take k . I.toAscList

trunc           :: Maze -> Maze
trunc (Maze rs) = Maze $ fmap (take' width) rs'
  where
    allWall       = F.all (== Wall)
    ix            = I.filter (not . allWall) rs
    (startR,endR) = (fst (I.findMin ix) - 2, 2 + fst (I.findMax ix))

    rs'   = slice' startR endR rs
    width = 2 + (fromMaybe 3 . F.maximum $ fmap lastFree rs')


lastFree = fmap (fst . fst) . I.maxViewWithKey . I.filter (== Free)


-- lastFree   :: Vector Field -> Maybe Int
-- lastFree v = let vi = V.findIndices (== Free) v
--              in if V.null vi then Nothing else Just $ V.last vi





slice' s e m = let (_,m') = I.split s m in fst $ I.split e m'

data Orientation = East | South | West | North deriving (Show,Eq,Ord,Enum)

type State' = State (Position,Orientation,Maze)


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

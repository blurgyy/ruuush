{-# LANGUAGE TupleSections #-}
{-# LANGUAGE FlexibleInstances #-}
module Main where

-- @EXPECTED_RESULTS@: TIMELIMIT

-- We duplicate each location t times, and then use maxFlow to find the number
-- of people we can save. We construct a graph G=(V,E) with |V| = O(lt) and |E|
-- = O((l+s)t).

-- FGL claims to use Edmonds-Karp to solve the maxflow problem itself. So
-- O(VE^2) in total, which is not going to fly.
--
import qualified Data.List as L
import           Data.Monoid
import           Data.Tuple

import qualified Data.IntSet as S

import           Data.Graph.Inductive
import qualified Data.Graph.Inductive.PatriciaTree as P

import           Data.Graph.Inductive.Query.MaxFlow2


-- import Data.GraphViz
-- import           Debug.Trace

-- instance Labellable (Location,Time) where
--   toLabelValue = toLabelValue . show

-- main = do
--   s <- readFile "sample.in"
--   let ps = readInput . tail . lines $ s
--   mapM_ (preview . buildGraph) ps


main = interact $ unlines . map (show . numResqueed) . readInput . tail . lines

type Location = Int
type Length = Int
type Capacity = Int
type Street = (Int,Int,Capacity,Length)

type MedFacility = Location
type Time = Int
type NumPeople = Int


data ProblemInstance = PI { numLocations :: Int
                          , startLocation  ::  Location
                          , numPeople :: NumPeople
                          , availableTime :: Time
                          , medFacilities :: [MedFacility]
                          , streets :: [Street]
                          } deriving (Show,Eq)

readInput :: [String] -> [ProblemInstance]
readInput [] = []
readInput (ls:ss:ms:xs) = let l = read ls
                              [s,p,t] = map read . words $ ss
                              m = read ms
                              (mss,ks:ys) = L.splitAt m xs
                              k = read ks
                              (sts,rest) = L.splitAt k ys
                          in (PI l s p t (map read mss) (map readStreet sts)) : readInput rest

readStreet   :: String -> Street
readStreet s = let [u,v,c,l] = map read . words $ s in (u,v,c,l)


numResqueed :: ProblemInstance -> NumPeople
numResqueed = maxFlow' . buildGraph
  where
    maxFlow' g = round . snd $ ekList g start sink

    -- buildGraph' pi = let gr = buildGraph pi in traceShow gr gr

type Used = Double
type Capacity' = Double

buildGraph :: ProblemInstance -> P.Gr () (Capacity',Used)
buildGraph pi = mkGraph (map f $ start:sink:vs) (startEdge : waitingEdges ++ sinkEdges ++ edges)
  where
    -- f v = (v,label (numLocations pi) v)
    f v = (v,())

    maxBound' = fromIntegral (maxBound :: Int)


    maxT = availableTime pi

    vs = map head . L.group . L.sort . concatMap (\(u,v,_) -> [u,v]) $ edges
    nodeId' = nodeId $ numLocations pi

    -- we release numPeople people at the starting location
    startEdge = (start, nodeId' (startLocation pi,0), (fromIntegral $ numPeople pi,0))

    -- we can always wait at a current location.
    waitingEdges = [ (nodeId' (l,t), nodeId' (l,t+1),(maxBound',0))
                   | t <- [0..maxT-1], l <- [1..numLocations pi]
                   ]

    -- the streets
    edges = [ (nodeId' (u,t), nodeId' (v,t+l),(fromIntegral c,0))
            | t <- [0..maxT] , (u,v,c,l) <- streets pi
            ]

    -- from a medical facility (and at any time <= maxT) we are saved. So, add an edge to a sink
    sinkEdges = [ (nodeId' (m,t), sink, (maxBound',0))
                | t <- [0..maxT] , m <- medFacilities pi
                ]

-- what about disconnected medical facilities? If you start on such a MF everything is ok.

start = -1

sink = 0


nodeId :: Int -> (Location,Time) -> Node
nodeId maxL (l,t) = t*maxL + l

label :: Int -> Node -> (Location,Time)
label maxL n = swap $ n `quotRem` maxL


--------------------------------------------------------------------------------

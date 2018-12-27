-- @EXPECTED_RESULTS@: CORRECT

{-# LANGUAGE TupleSections #-}
module Main where

-- import           Data.Graph.Inductive
-- import           Data.Graph.Inductive.PatriciaTree
-- import           Data.Graph.Inductive.Query.SP

import qualified  Data.IntMap as IM

import qualified Data.Graph.Inductive.Internal.Heap as H
import qualified Data.IntSet as S
import Data.List(group,sort)
import           Data.Maybe

import           Debug.Trace


main = interact $ unlines . map (showSteps . minSteps) . readInput . tail . lines

type Button = Int

type Instance = (Time,[Button])
type Time = Int

maxS = 3600

readInput [] = []
readInput (x:y:rs) = let f = map read . words
                         [_,t] = f x
                     in (t,f y) : readInput rs

showSteps (k,t) = unwords . map show $ [k,t]

minSteps         :: Instance -> (Int,Time)
-- minSteps (gt,bs) | traceShow (gt,bs) False = undefined
minSteps (gt,bs) = let (es,nss) = gen bs 0 [] S.empty
                       t        = fromJust . S.lookupGE gt $ nss
                       gr       = fromEdges es
                   in (spLength 0 t gr, t - gt)


type Node = Int
type LEdge a = (Node,Node,a)

spLength      :: (Show a,Ord a, Num a) => Node -> Node -> Graph a -> a
spLength s t g = fromJust . IM.lookup t $ dijkstra (H.unit 0 s) g IM.empty
-- spLength s t g = fromJust . IM.lookup t $ dists
--   where
--     dists' = dijkstra (H.unit 0 s) g IM.empty
--     dists = traceShow dists' dists'


type PriQ pri a = H.Heap pri a

type Distances a = IM.IntMap a




dijkstra :: (Ord a, Num a) => PriQ a Node -> Graph a -> Distances a -> Distances a
dijkstra pq g@(Graph gm) dists
  | H.Empty == pq = dists
  | otherwise = if v `IM.member` dists
                then dijkstra pq'  g   dists
                else dijkstra pq'' g $ IM.insert v dv dists
  where
    (dv,v,pq')   = H.splitMin pq
    pq''         = foldr updateDist pq' neighs
    neighs       = filter (\(u,_) -> u `IM.notMember` dists) $ neighbours v g

    updateDist (u,dvu) = H.insert ((dv + dvu),u)


newtype Graph a = Graph { unG :: IM.IntMap [(Node,a)] }  deriving (Show,Eq)

neighbours v = fromMaybe [] . IM.lookup v . unG

fromEdges :: [LEdge a] -> Graph a
fromEdges = Graph . foldr (\(u,v,l) -> IM.insertWith (++) u [(v,l)]) IM.empty



testG = fromEdges [(1,2,1),(2,3,1),(2,4,1),(3,4,1),(4,1,1)]

-- generates the edges reachable from time t. This is basically a DFS
gen :: [Button] -> Time -> [LEdge Int] -> S.IntSet -> ([LEdge Int], S.IntSet)
gen bs t es visited
  | t `S.member` visited = (es,visited)
  | otherwise            = foldr visit (neighEdges ++ es,t `S.insert` visited) neighs
  where
    neighs = reach t $ bs
    neighEdges = map (t,,1) neighs
    visit t' (es',vs') = gen bs t' es' vs'

-- We use that the buttons are in sorted order. And drop all the nodes that are
-- not in the range [0..maxS]
reach   :: Time -> [Button] -> [Time]
reach t = map head . group . map (clamp . (t +))
  where
    clamp t' = 0 `max` (t' `min` maxS)

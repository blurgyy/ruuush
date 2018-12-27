-- @EXPECTED_RESULTS@: CORRECT

{-# LANGUAGE TupleSections #-}
module Main where

-- Basic construction: generate a graph of all times that are reachable, then
-- compute a shortest path to the smallest node/time that is at least the goal
-- time.

-- Running time: O(Tn log T) modulo fgl running times (this may give an
-- additonal log T factor or so, depending on the data structure used to
-- represent the (inductive) graph)

import           Data.Graph.Inductive
import qualified Data.Graph.Inductive.PatriciaTree as P
import           Data.Graph.Inductive.Query.SP
import           Data.Maybe
import Data.List(group,sort)
import qualified Data.IntSet as S

import           Debug.Trace


main = interact $ unlines . map (showSteps . minSteps) . readInput . tail . lines

type Button = Int

type Instance = (Time,[Button])
type Time = Int

maxS = 3600

nub' = map head . group . sort

-- Note the nub: somehow gen messes up if we have multiple buttons with the same time amount.
readInput [] = []
readInput (x:y:rs) = let f = map read . words
                         [_,t] = f x
                     in (t,nub' $ f y) : readInput rs

showSteps (k,t) = unwords . map show $ [k,t]

minSteps         :: Instance -> (Int,Time)
-- minSteps (gt,bs) | traceShow (gt,bs) False = undefined
minSteps (gt,bs) = let (es,nss) = gen bs 0 [] S.empty
                       t        = fromJust . S.lookupGE gt $ nss
                       gr       = mkG (S.toList nss) es
                   in (spLength 0 t gr, t - gt)

mkG    :: [Node] -> [LEdge Int] -> P.Gr () Int
mkG vs = mkGraph $ map (,()) vs


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

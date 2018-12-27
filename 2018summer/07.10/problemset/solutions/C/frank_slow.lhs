@EXPECTED_RESULTS@: TIMELIMIT
---
title: Slow Army Base
author: Frank Staals
---

Army Base Naive
=============================

$O(n^3)$ solution.


> {-# LANGUAGE GeneralizedNewtypeDeriving #-}
> module Main where

> import Control.Applicative

> import Data.List
> import Data.Ord

> import Data.Monoid
> import Data.Ix
> import Data.Function(on)
>
> import qualified Data.Array   as A

> import qualified Data.List     as L

> import Debug.Trace



Preliminaries
-------------

> newtype Point = Point (Int,Int)
>               deriving (Show,Eq)


> getX, getY :: Point -> Int
> getX (Point (x,_)) = x
> getY (Point (_,y)) = y


> type PointSet = [Point]


A value of type Half should still be halved. I.e. 'Half 2x = x'

> newtype Half = Half Int
>                        deriving (Show,Eq,Ord)
>
> instance Num Half where
>   (Half a) + (Half b) = Half $ a + b
>   (Half a) - (Half b) = Half $ a - b
>   (Half a) * (Half b) = Half $ a * b
>   abs (Half a) = Half $ abs a
>   signum (Half a) = Half $ 2 * signum a
>   fromInteger a = Half $ 2 * fromInteger a

> showValue :: Half -> String
> showValue (Half i) = concat [ show $ i `div` 2
>                             , if odd i then ".5" else ""
>                             ]
>   where
>     odd x = x `mod` 2 /= 0


> type Area = Half



TODO: Discuss degenerate cases here


Let $V(Q)$ denote the vertices of polygon $Q$, and let $\mathcal{CH}(P)$ denote
the convex hull of the set of points $P$.


<div class="lemma">
There is an maximum area quadrangle $Q^*$, such that $V(Q^*) \subseteq
V(\mathcal{CH}(P))$.
</div>

<div class="proof">
TODO
</div>



Main Algorithm
---------------

> maxBaseArea p = let (ConvexHull pch) = convexHull p
>                 in maxAreaTriangle pch `max` maxAreaQuadrangle pch

<div class="observation">
Left an Right chains are independent
</div>


Try all triplets in O(n^3) time:

> maxAreaTriangle ps = maximum' [ area $ Triangle (a,b,c)
>                              | a <- ps, b <- ps, c <- ps]


Main idea: Pick two vertices as diagonal this splits the quadrangle in two
disjoint triangles. Find the max area triangle naively by trying all
options. Again this takes $O(n^3) time.

> maxAreaQuadrangle    :: PointSet -> Area
> maxAreaQuadrangle ps = maximum' [ maxAreaQuadrangleWith p q ps
>                                | p <- ps , q <- ps , p /= q
>                                ]

-- > maxAreaQuadrangle ps = traceShow max' (fst max')
-- >   where
-- >     max'  = maximumBy (comparing fst) all'
-- >     all' = (0,undefined) : [ (maxAreaQuadrangleWith p q ps, (p,q))
-- >            | p <- ps , q <- ps , p /= q
-- >            ]


> maximum' = maximum . (0 :)

> newtype Line = Line (Point,Point)

> splitPointSet :: Line -> PointSet -> (PointSet,PointSet)
> splitPointSet (Line (p,q)) = L.partition (\r -> rightTurn p r q)


> rightTurn       :: Point -> Point -> Point -> Bool
> rightTurn a b c = ccw a b c == CW


> data CCW = CCW | CoLinear | CW
>          deriving (Show,Eq)

> ccw                                                 :: Point -> Point -> Point -> CCW
> ccw (Point (px,py)) (Point (qx,qy)) (Point (rx,ry)) = case compare z 0 of
>                                                         LT -> CW
>                                                         GT -> CCW
>                                                         EQ -> CoLinear
>     where
>       (ux,uy) = (qx - px, qy - py)
>       (vx,vy) = (rx - px, ry - py)
>       z       = ux * vy - uy * vx






We then use `maxAreaQuadrangleWith` to find the largest quadrangle given its
diagonals $p$ and $q$ (and the pointset)

> maxAreaQuadrangleWith             :: Point -> Point -> PointSet -> Area
> maxAreaQuadrangleWith p q ps = let (us,vs) = splitPointSet (Line (p,q)) ps
>                                in   maxAreaTriangleWith p q us
>                                   + maxAreaTriangleWith p q vs


> maxAreaTriangleWith p q = maximum' . map (\r -> area $ Triangle (p,q,r))


> newtype Triangle = Triangle (Point,Point,Point)
>                    deriving (Show,Eq)


Based on determinant of a 3x3 matrix (shoelace formula)

> area                                                                :: Triangle -> Half
> area (Triangle ((Point (ax,ay)), (Point (bx,by)), (Point (cx,cy)))) =
>   Half . abs $ ax*by - ax*cy
>              + bx*cy - bx*ay
>              + cx*ay - cx*by


Input & Output
--------------

> readPointSet :: [String] -> PointSet
> readPointSet = map readPoint
>   where
>     readPoint s = let [x,y] = map read . words $ s in Point (x,y)

> readInput           :: [String] -> [PointSet]
> readInput []        = []
> readInput (ns:rest) = let n       = read ns
>                           (xs,ys) = L.splitAt n rest
>                       in readPointSet xs : readInput ys

> main :: IO ()
> main = interact $
>          unlines . map (showValue . maxBaseArea) . readInput . tail . lines

-- > main :: IO ()
-- > main = readFile "testdata_ipe.in" >>=
-- >        putStr . unlines . map (showValue . maxBaseArea) . readInput . tail . lines


Array Stuff
-----------

> data Array i a = Array { bounds       :: (i,i)
>                        , accessTransf :: i -> i
>                        , arrayData    :: A.Array i a
>                        }

> instance Ix i => Functor (Array i) where
>   fmap f (Array b g a) = Array b g (fmap f a)


> (!) :: Ix i => Array i a -> i -> a
> (Array _ g a) ! i = a A.! (g i)

> elems                   :: Ix i => Array i a -> [a]
> elems a = [ a ! i | i <- A.range $ bounds a ]

> listArray   :: Ix i => (i,i) -> [a] -> Array i a
> listArray b = Array b id . A.listArray b


> ixSubMap :: Ix i => (i,i) -> (i -> i) -> Array i a -> Array i a
> ixSubMap bs f (Array obs g a) = Array bs (g . f) a



Testing stuff
-------------

> testPs :: PointSet
> testPs = [Point (0,0), Point (2,2), Point (4,1), Point (5,0), Point (3,-1)]

> test2 = [Point (0,0), Point (-2,-2), Point (3,-2), Point (0,1), Point (0,3)]



Computing the Convex Hull
-------------------------

The standard Graham scan algorithm to compute the convex hull of a set of
points in $O(n \log n)$ time.

> newtype ConvexHull = ConvexHull [Point]
>                      deriving (Show,Eq)

> convexHull     :: PointSet -> ConvexHull
> convexHull []  = ConvexHull []
> convexHull [p] = ConvexHull [p]
> convexHull ps  = let ps' = L.sortBy incXdecY ps
>                      uh  = tail . hull . Sorted $         ps'
>                      lh  = tail . hull . Sorted $ reverse ps'
>                  in ConvexHull $ lh ++ uh

> incXdecY (Point (px,py)) (Point (qx,qy)) =
>   compare px qx <> compare qy py


> newtype Sorted s a = Sorted { unS :: s a }
>                      deriving (Show,Eq,Ord,Read,Functor)


> hull                   :: Sorted [] Point -> [Point]
> hull (Sorted (a:b:ps)) = hull' [b,a] ps
>   where
>     hull' h  []    = h
>     hull' h (p:ps) = hull' (cleanMiddle (p:h)) ps
>
>     cleanMiddle [b,a]          = [b,a]
>     cleanMiddle h@(c:b:a:rest)
>       | rightTurn a b c       = h
>       | otherwise             = cleanMiddle (c:a:rest)

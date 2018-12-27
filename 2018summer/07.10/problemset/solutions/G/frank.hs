-- @EXPECTED_RESULTS@: CORRECT
module Main where

import Data.List
import Data.Ord


main = interact $ unlines . map (showGear . maxGear) . readInput . tail . lines


type ProblemInstance = [Gear]

type Gear = (Int,Parabola)
type Parabola = (Double,Double,Double)


readInput         :: [String] -> [ProblemInstance]
readInput []      = []
readInput (ns:ss) = let n = read ns
                        (gs,rest) = splitAt n ss
                    in zipWith readGear [1..] gs : readInput rest

readGear i s = let [a,b,c] = map read . words $ s in (i,(a,b,c))


showGear ((i,_), r) = unwords . map show $ [i]
-- ,round' r]
--  where
--    round' x | x - fromIntegral (floor x) >= 0.5 = ceiling x
--             | otherwise                         = floor x



type RPM = Double
type Torque = Double

maxGear :: ProblemInstance -> (Gear,RPM)
maxGear = (\(g,r,_) -> (g,r)) . maximumBy (comparing td) . map f
  where
    td (_,_,c) = c
    f g = let r = maxTorqueAt g in (g,r,torque g r)

maxTorqueAt             :: Gear -> RPM
maxTorqueAt (_,(a,b,_)) = b / (2 * a)

torque               :: Gear -> RPM -> Torque
torque (_,(a,b,c)) r = -1 * a * r * r + b * r + c

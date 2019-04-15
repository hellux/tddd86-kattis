import Data.Function (on)
import Data.List (sortBy)
import Text.Printf

ratios :: [Integer] -> [Integer] -> [Double]
ratios fs rs = ((/) `on` fromIntegral) <$> rs <*> fs

maxSpread :: [Integer] -> [Integer] -> Double
maxSpread fs rs = maximum . spreads . sortBy (flip compare) $ ratios fs rs where
    spreads :: [Double] -> [Double]
    spreads = (zipWith (/)) <*> tail

solve xs = map (uncurry maxSpread) xs

parseInput :: String -> [([Integer], [Integer])]
parseInput = testCase . lines where
    parseInts = map read . words
    testCase [_] = []
    testCase (_:fs:rs:xs) = (parseInts fs, parseInts rs):testCase xs

formatOutput :: [Double] -> String
formatOutput = unlines . map (printf "%.2f") where

main = interact (formatOutput . solve . parseInput)

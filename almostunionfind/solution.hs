import qualified Data.Set as Set

data Instruction = Union Int Int | Move Int Int | Print Int deriving (Show)
data Case = Case Int [Instruction]
type Sets = [Set.Set Int]
type Printout = (Int, Int)

execute :: (Sets, [Printout]) -> Instruction -> (Sets, [Printout])
execute (sets, ps) (Union src dst) = (sets, ps)
execute (sets, ps) (Move src dst) = (sets, ps)
execute (sets, ps) (Print set) = (sets, ps)

initial :: Int -> (Sets, [Printout])
initial size = ([Set.singleton i | i <- [1..size]], [])

executeCase :: Case -> [Printout]
executeCase (Case size instr) = snd $ foldl execute (initial size) instr

solve :: [Case] -> [Printout]
solve = concatMap executeCase

parseInput :: String -> [Case]
parseInput = parseCases . map (map read . words) . lines where
    parseInstr :: [Int] -> Instruction
    parseInstr [1,src,dst] = Union src dst
    parseInstr [2,src,dst] = Move src dst
    parseInstr [3,set] = Print set
    parseCases :: [[Int]] -> [Case]
    parseCases [] = []
    parseCases ([n,m]:xs) =
        Case n (map parseInstr (take m xs)) : parseCases (drop m xs)

formatOutput :: [Printout] -> String
formatOutput = unlines . map formatLine where 
    formatLine :: Printout -> String
    formatLine (n, sum) = unwords $ map show [n, sum]

main = interact (formatOutput . solve . parseInput)

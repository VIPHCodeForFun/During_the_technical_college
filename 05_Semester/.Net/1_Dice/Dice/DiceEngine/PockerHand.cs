/*
 Class for processing and validating a poker hand.
 Vidmar/Brescher
*/

using System;
using System.Collections.Generic;
using System.Diagnostics.Contracts;
using System.Linq;
using System.Net.Security;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace DiceEngine
{
    /// <summary>
    /// Class <c>PockerHand</c> processes and validates a poker hand.
    /// </summary>
    public class PockerHand
    {
        /// <summary>
        /// This method validates a DiceSet instance against known poker hands.
        /// </summary>
        /// <param name="diceSet">DiceSet to check.</param>
        /// <returns>String representating the poker hand of the given DiceSet.</returns>
        public String CheckRoll(DiceSet diceSet)
        {
            // validate the set against poker hands in order.
            var validatedPokerHand = "Nothing";
            validatedPokerHand = OnePair(diceSet, validatedPokerHand);
            validatedPokerHand = TwoPairs(diceSet, validatedPokerHand);
            validatedPokerHand = ThreeOfaKind(diceSet, validatedPokerHand);
            validatedPokerHand = LowStright(diceSet, validatedPokerHand);
            validatedPokerHand = HighStright(diceSet, validatedPokerHand);
            validatedPokerHand = FullHuse(diceSet, validatedPokerHand);
            validatedPokerHand = FourOfaKind(diceSet, validatedPokerHand);
            validatedPokerHand = FiveOfaKind(diceSet, validatedPokerHand);
            return validatedPokerHand;
        }

        /// <summary>
        /// Checks if a given DiceSet is a <c>Five of a kind</c> poker hand, e.g. five tens.
        /// </summary>
        /// <param name="diceSet">DiceSet to check.</param>
        /// <param name="result">Default return value if not matched.</param>
        /// <returns>String representating the poker hand if matched, or default return value.</returns>
        private string FiveOfaKind(DiceSet diceSet, string result)
        {
            var firstElement = diceSet.RolledDiceSide.First();
            foreach (var item in diceSet.RolledDiceSide)
            {
                if (firstElement.Name != item.Name)
                {
                    return result;
                }
            }
            return "Five of a kind";
        }

        /// <summary>
        /// Checks if a given DiceSet is a <c>Four of a kind</c> poker hand, e.g. four jacks.
        /// </summary>
        /// <param name="diceSet">DiceSet to check.</param>
        /// <param name="result">Default return value if not matched.</param>
        /// <returns>String representating the poker hand if matched, or default return value.</returns>
        private string FourOfaKind(DiceSet diceSet, string result)
        {
            int numberOfEqual = 0;
            foreach (var comparator in diceSet.RolledDiceSide)
            {
                foreach (var item in diceSet.RolledDiceSide)
                {
                    if (comparator.Name == item.Name)
                    {
                        numberOfEqual++;
                    }
                    if (numberOfEqual == 4)
                    {
                        return "Four of a kind";
                    }
                }
                numberOfEqual = 0;
            }
            return result;
        }

        /// <summary>
        /// Checks if a given DiceSet is a <c>Full house</c> poker hand, e.g. three aces and two queens.
        /// </summary>
        /// <param name="diceSet">DiceSet to check.</param>
        /// <param name="result">Default return value if not matched.</param>
        /// <returns>String representating the poker hand if matched, or default return value.</returns>
        private string FullHuse(DiceSet diceSet, string result)
        {
            List<int> counterList = new List<int>();
            int count = 0;

            // Count the number of equal values and write them in the list
            foreach (var comparator in diceSet.RolledDiceSide)
            {
                count = 0;
                foreach (var item in diceSet.RolledDiceSide)
                {
                    if (comparator.Name == item.Name)
                    {
                        count++;
                    }
                }
                counterList.Add(count);
            }

            // Check if there are only 3 or 2 in the list
            count = 0;
            foreach (var item in counterList)
            {
                if (item == 2 || item == 3)
                {
                    count++;
                }
            }
            if (count == 5)
            {
                return "Full house";
            }
            return result;
        }

        /// <summary>
        /// Checks if a given DiceSet is a <c>High straight</c> poker hand, the five consecutive values A-K-D-B-10.
        /// </summary>
        /// <param name="diceSet">DiceSet to check.</param>
        /// <param name="result">Default return value if not matched.</param>
        /// <returns>String representating the poker hand if matched, or default return value.</returns>
        private string HighStright(DiceSet diceSet, string result)
        {
            var highStraightComparator = new List<String>() { "Ace", "King", "Queen", "Jack", "10" };
            var rolledSides = new List<String>();

            // only applies to DiceSet of 5 Dices
            if (diceSet.RolledDiceSide.Count != 5) return result;

            foreach (var item in diceSet.RolledDiceSide)
            {
                rolledSides.Add(item.Name);
            }

            // check for equal elements using HashSet
            if (new HashSet<String>(highStraightComparator).SetEquals(rolledSides))
            {
                // RolledSides.ForEach(p => Console.WriteLine(p));
                return "High straight";
            }
            return result;
        }

        /// <summary>
        /// Checks if a given DiceSet is a <c>Low straight</c> poker hand, the five consecutive values K-D-B-10-9.
        /// </summary>
        /// <param name="diceSet">DiceSet to check.</param>
        /// <param name="result">Default return value if not matched.</param>
        /// <returns>String representating the poker hand if matched, or default return value.</returns>
        private string LowStright(DiceSet diceSet, string result)
        {
            var lowStraightComperator = new List<String>() { "King", "Queen", "Jack", "10", "9" };
            var rolledSides = new List<String>();

            // only applies to DiceSet of 5 Dices
            if (diceSet.RolledDiceSide.Count != 5) return result;


            foreach (var item in diceSet.RolledDiceSide)
            {
                rolledSides.Add(item.Name);
            }

            // check for equal elements using HashSet
            if (new HashSet<String>(lowStraightComperator).SetEquals(rolledSides))
            {
                return "Low straight";
            }
            return result;
        }

        /// <summary>
        /// Checks if a given DiceSet is a <c>Three of a kind</c> poker hand, e.g., three aces.
        /// </summary>
        /// <param name="diceSet">DiceSet to check.</param>
        /// <param name="result">Default return value if not matched.</param>
        /// <returns>String representating the poker hand if matched, or default return value.</returns>
        private string ThreeOfaKind(DiceSet diceSet, string result)
        {
            int numberOfEqual = 0;
            foreach (var comparator in diceSet.RolledDiceSide)
            {
                foreach (var item in diceSet.RolledDiceSide)
                {
                    if (comparator.Name == item.Name)
                    {
                        numberOfEqual++;
                    }
                    if (numberOfEqual == 3)
                    {
                        return "Three of a kind";
                    }
                }
                numberOfEqual = 0;
            }
            return result;
        }

        /// <summary>
        /// Checks if a given DiceSet is a <c>Two pairs</c> poker hand, e.g. two jacks and two nines; here the highest pair is scored.
        /// </summary>
        /// <param name="diceSet">DiceSet to check.</param>
        /// <param name="result">Default return value if not matched.</param>
        /// <returns>String representating the poker hand if matched, or default return value.</returns>
        private string TwoPairs(DiceSet diceSet, string result)
        {
            List<int> counterList = new List<int>();
            int count = 0;

            foreach (var comparator in diceSet.RolledDiceSide)
            {
                count = 0;
                foreach (var item in diceSet.RolledDiceSide)
                {
                    if (comparator.Name == item.Name)
                    {
                        count++;
                    }
                }
                counterList.Add(count);
            }
            count = 0;
            foreach (var item in counterList)
            {
                if (item == 2)
                {
                    count++;
                }
            }
            if (count == 4)
            {
                return "Two pairs";
            }

            return result;
        }

        /// <summary>
        /// Checks if a given DiceSet is a <c>One pair</c> poker hand, e.g. two Tens.
        /// </summary>
        /// <param name="diceSet">DiceSet to check.</param>
        /// <param name="result">Default return value if not matched.</param>
        /// <returns>String representating the poker hand if matched, or default return value.</returns>
        private string OnePair(DiceSet diceSet, string result)
        {
            int numberOfEqual = 0;
            foreach (var comparator in diceSet.RolledDiceSide)
            {
                foreach (var item in diceSet.RolledDiceSide)
                {
                    if (comparator.Name == item.Name)
                    {
                        numberOfEqual++;
                    }
                    if (numberOfEqual == 2)
                    {
                        return "One pair";
                    }
                }
                numberOfEqual = 0;
            }
            return result;
        }

    }

}

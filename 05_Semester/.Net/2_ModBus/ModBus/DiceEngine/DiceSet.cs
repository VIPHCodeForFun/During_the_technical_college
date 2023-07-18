/*
 Class that models a set of <c>Dice<c> objects.
 Vidmar/Brescher
*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DiceEngine
{
    /// <summary>
    /// Class <c>DiceSet</c> represents a set of <c>Dice</c> objects.
    /// </summary>
    public class DiceSet
    {
        /// <summary>
        /// Property <c>DiceSideList</c> represents the <c>Dice</c> objects in this set.
        /// </summary>
        public IReadOnlyList<Dice> DiceSideList { get; private set; }
        private List<Dice> _diceSideList;

        /// <summary>
        /// List of the rolled <c>DiceSide</c> of the <c>Dice</c> in this set.
        /// </summary>
        public List<DiceSide> RolledDiceSide;

        /// <summary>
        /// This constructor initializes a new <c>DiceSet</c>.
        /// </summary>
        public DiceSet()
        {
            _diceSideList = new List<Dice>();
            DiceSideList = _diceSideList;

            RolledDiceSide = RollAllDice();
        }

        /// <summary>
        /// This constructor initializes a new <c>DiceSet</c> with a given <c>Dice</c> object.
        /// </summary>
        /// <param name="diceType"><c>Dice</c> object for this set.</param>
        /// <param name="numberOfDices">Number of Dices in this set.</param>
        public DiceSet(Dice diceType, int numberOfDices)
        {
            _diceSideList = new List<Dice>();
            for (int i = 0; i < numberOfDices; i++)
            {
                _diceSideList.Add(diceType);
            }
            DiceSideList = _diceSideList;

            RollAllDice();
        }

        /// <summary>
        /// This method adds a single Dice to this set.
        /// </summary>
        /// <param name="dice"></param>
        public void AddDice(Dice dice)
        {
            _diceSideList.Add(dice);
        }

        /// <summary>
        /// This method removes a single Dice from this set.
        /// </summary>
        /// <param name="dice"></param>
        public void RemoveDice(Dice dice)
        {
            _diceSideList.Remove(dice);
        }

        /// <summary>
        /// This method rolls a random DiceSide for each Dice in the set.
        /// </summary>
        /// <returns>List of rolled DiceSides for the Dice in this set.</returns>
        public List<DiceSide> RollAllDice()
        {
            List<DiceSide> rolledDiceSides = new List<DiceSide>();
            foreach (Dice dice in _diceSideList)
            {
                rolledDiceSides.Add(dice.Roll());
            }
            this.RolledDiceSide = rolledDiceSides;
            return rolledDiceSides; 
        }

        /// <summary>
        /// This method prints the DiceSides of each Dice in the set.
        /// </summary>
        public void PrintDiceSet()
        {
            foreach (DiceSide dice in RolledDiceSide)
            {
                    System.Console.WriteLine(dice.Name);
            }
            return;
        }
       
    }
}

/*
 Class that models <c>Dice<c> objects.
 Vidmar/Brescher
*/

using System;
using System.Xml.Linq;

namespace DiceEngine
{
    /// <summary>
    /// Class <c>Dice</c> represents a Dice with 1 to n sides.
    /// </summary>
    public class Dice
    {
        /// <summary>
        /// Property <c>DiceSides</c> represents the <c>DiceSide</c> objects on this Dice.
        /// </summary>
        public IReadOnlyList<DiceSide> DiceSides { get; private set; }
        private List<DiceSide> _diceSides;

        private readonly Random _random;

        /// <summary>
        /// This constructor initializes a new <c>Dice</c>.
        /// </summary>
        public Dice()
        {
            _diceSides = new List<DiceSide>();
            DiceSides = _diceSides;

            _random = new Random();
        }

        /// <summary>
        /// This method adds a single DiceSide to this Dice.
        /// </summary>
        /// <param name="diceSide"><c>DiceSide</c> to add.</param>
        public void AddSide(DiceSide diceSide)
        {
            _diceSides.Add(diceSide);
        }
        /// <summary>
        /// This method adds a single DiceSide to this Dice.
        /// </summary>
        /// <param name="name">String representation of <c>DiceSide</c> to add.</param>
        public void AddSide(string name)
        {
            _diceSides.Add(new DiceSide(name));
        }

        /// <summary>
        /// This method removes a single DiceSide to this Dice.
        /// </summary>
        /// <param name="diceSide"><c>DiceSide</c> to remove.</param>
        public void RemoveSide(DiceSide diceSide)
        {
            _diceSides.Remove(diceSide);
        }
        /// <summary>
        /// This method removes a single DiceSide to this Dice.
        /// </summary>
        /// <param name="name">String representation of <c>DiceSide</c> to remove.</param>
        public void RemoveSide(string name)
        {
            foreach (var diceSide in _diceSides)
            {
                if (diceSide.Name == name)
                {
                    _diceSides.Remove(diceSide);
                }
            }
        }

        /// <summary>
        /// This method rolls the faces of the Dice randomly.
        /// </summary>
        /// <returns>Rolled DiceSide</returns>
        public DiceSide Roll()
        {
            return _diceSides[_random.Next(_diceSides.Count)];
        }
    }
}
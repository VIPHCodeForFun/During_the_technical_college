/*
 Class that models a side of a Dice class.
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
    /// Class <c>DiceSide</c> represents the face/side of a Dice.
    /// </summary>
    public class DiceSide
    {
        /// <summary>
        /// Instance variable <c>Name</c> represents the given name of the DiceSide.
        /// </summary>
        public string Name { get; private set; }
        
        /// <summary>
        /// Constructs a DiceSide
        /// </summary>
        /// <param name="name">String representing the face/side of a Dice.</param>
        public DiceSide(string name)
        {
            Name = name;
        }
    }
}

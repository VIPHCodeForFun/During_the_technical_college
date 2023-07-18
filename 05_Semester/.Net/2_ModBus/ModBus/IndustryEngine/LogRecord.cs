/*
 Class for ...
 Vidmar/Brescher
*/
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace IndustryEngine
{
    /// <summary>
    /// Class to log Records
    /// </summary>
    internal class LogRecord
    {
        /// <summary>
        /// Time Stamp <c>Unixts</c>
        /// </summary>
        public long Unixts { get; set; }

        /// <summary>
        /// Count of Itemns <c>NumberOfItems</c>
        /// </summary>
        public int NumberOfItems { get; set; }

        /// <summary>
        /// Constructor for a new <c>LogRecord</c>
        /// </summary>
        /// <param name="unixts"></param>
        /// <param name="numberOfItems"></param>
        public LogRecord(long unixts, int numberOfItems)
        {
            Unixts = unixts;
            NumberOfItems = numberOfItems;
        }
    }
}

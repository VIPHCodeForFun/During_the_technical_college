/*
 Test-Applikation zur Aufgabe aus NET LB01
 Vidmar/Brescher
*/

using DiceEngine;
using System.Diagnostics.CodeAnalysis;
using System.Runtime.CompilerServices;
using System.Xml.Linq;
using static System.Net.Mime.MediaTypeNames;

// Available dice pages
DiceSide dAce = new DiceSide("Ace");
DiceSide dKing = new DiceSide("King");
DiceSide dQueen = new DiceSide("Queen");
DiceSide dJack = new DiceSide("Jack");
DiceSide d10 = new DiceSide("10");
DiceSide d9 = new DiceSide("9");

// Compose a dice
Dice diceOne = new Dice();
diceOne.AddSide(dAce);
diceOne.AddSide(dKing);
diceOne.AddSide(dQueen);
diceOne.AddSide(dJack);
diceOne.AddSide(d10);
diceOne.AddSide(d9);

Console.WriteLine("Test - Applikation zur Aufgabe aus NET LB01");
Console.WriteLine("Vidmar/Brescher\n");

//  Simulation of the operation Dice ⇒ Returns a randomly selected dice page.
Console.WriteLine("Single roll: " + diceOne.Roll().Name + "\n");

// Test create a diceset
DiceSet dicePoker = new DiceSet(diceOne, 5);

// Test Roll a diceset
dicePoker.RollAllDice();
Console.WriteLine("DiceSet roll: ");
dicePoker.PrintDiceSet();

// Testing the probabilities for the PockerHand
PockerHand myHand = new PockerHand();
var result = "empty";

double[] calculateArray = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
// [0] Five of a kind
// [1] Four of a kind
// [2] Full house
// [3] High straight
// [4] Low straight
// [5] Three of a kind
// [6] Two pairs
// [7] One pair
// [8] Runt;
Console.WriteLine("\n-- -- -- -- letz play 10 000 000 games -- -- -- --");
int count = 0;
for (count = 0; count < 10000000; count++)
{
    result = myHand.CheckRoll(dicePoker);
    switch (result)
    {
        case "Five of a kind": calculateArray[0]++; break;
        case "Four of a kind": calculateArray[1]++; break;
        case "Full house": calculateArray[2]++; break;
        case "High straight": calculateArray[3]++; break;
        case "Low straight": calculateArray[4]++; break;
        case "Three of a kind": calculateArray[5]++; break;
        case "Two pairs": calculateArray[6]++; break;
        case "One pair": calculateArray[7]++; break;
        default: calculateArray[8]++; break;
    }
    dicePoker.RollAllDice();
}

Console.WriteLine("{0,-25}:{1,7:0.00}%", "Five of a kind", (calculateArray[0] / (double)count) * 100);
Console.WriteLine("{0,-25}:{1,7:0.00}%", "Four of a kind", (calculateArray[1] / (double)count) * 100);
Console.WriteLine("{0,-25}:{1,7:0.00}%", "Full house", (calculateArray[2] / (double)count) * 100);
Console.WriteLine("{0,-25}:{1,7:0.00}%", "High straight", (calculateArray[3] / (double)count) * 100);
Console.WriteLine("{0,-25}:{1,7:0.00}%", "Low straight", (calculateArray[4] / (double)count) * 100);
Console.WriteLine("{0,-25}:{1,7:0.00}%", "Any Straight", ((calculateArray[4] + calculateArray[3]) / (double)count) * 100);
Console.WriteLine("{0,-25}:{1,7:0.00}%", "Three of a kind", (calculateArray[5] / (double)count) * 100);
Console.WriteLine("{0,-25}:{1,7:0.00}%", "Two pairs", (calculateArray[6] / (double)count) * 100);
Console.WriteLine("{0,-25}:{1,7:0.00}%", "One pair", (calculateArray[7] / (double)count) * 100);
Console.WriteLine("{0,-25}:{1,7:0.00}%", "Runt", (calculateArray[8] / (double)count) * 100);

double sum = calculateArray.Sum() / (double)count * 100.0;
Console.WriteLine(String.Format("{0,-25}:{1,7:0.00}%", "Sum", sum));
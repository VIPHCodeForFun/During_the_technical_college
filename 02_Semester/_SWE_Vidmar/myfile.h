/*
 * myfile.h
 *
 *  Created on: 09.03.2021
 *      Author: Simon
 */

#ifndef MYFILE_H_
#define MYFILE_H_

/*
 * Die Funktion Oeffnet die Datei hinter path als Text-Datei und gibt den Inhalt auf
 * stdout wieder aus. Ist die Datei nicht vorhanden oder gesperrt wird ein Hinweis auf stdout
 * ausgegeben.
*/
void catTextFile(char *path);
void catTextFile_(char *path);
void copyTextFile(char *src, char *dst);

#endif /* MYFILE_H_ */

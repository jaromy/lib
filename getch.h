/* getch - emulates the function from DOS / Windows. Fetches a single character from stdin, without waiting for
 *			a terminating newline character.
 */

#ifdef __cplusplus
extern "C" {
#endif

	char getch(void);
	char getche(void); 		//with echo
	
#ifdef __cplusplus
}
#endif
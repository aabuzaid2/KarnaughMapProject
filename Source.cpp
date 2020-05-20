#include <iostream> 
#include<string>
#include<iomanip>

using namespace std;

int main()
{
	int* input, n;
	int Kmap[2][4];
	cout << "How many numbers? " << endl;
	cin >> n;

	while (n > 8) {
		cout << "ERROR! You Can't Enter More Than 8 Integers, Try Again!\n";
		cin >> n;
	}

	//user minterms input

	input = new int[n];
	cout << "Enter Numbers: " << endl;			
	for (int i = 0; i < n; i++) {
		cin >> input[i];
		while (input[i] > 7) {
			cout << "ERROR! The number you enter must be between 0 and 7, Try again...\n";
			cin >> input[i];
		}
	}

	//setting all the kmap to zeros

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {

			Kmap[i][j] = 0;
		}

	}

	//checking and writing the Kmap

	for (int i = 0; i < n; i++) {


		if (input[i] == 0) {

			Kmap[0][0] = 1;
		}

		else if (input[i] == 1) {

			Kmap[1][0] = 1;
		}

		else if (input[i] == 2) {

			Kmap[0][1] = 1;
		}

		else if (input[i] == 3) {

			Kmap[1][1] = 1;
		}

		else if (input[i] == 4) {

			Kmap[0][3] = 1;
		}

		else if (input[i] == 5) {

			Kmap[1][3] = 1;
		}

		else if (input[i] == 6) {

			Kmap[0][2] = 1;
		}

		else if (input[i] == 7) {

			Kmap[1][2] = 1;
		}

	}

	//displaying the Kmap

	cout << "K-Map =" << endl;

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {

			cout << Kmap[i][j] << "  ";
		}
		cout << endl;
	}

	cout << "F = \n";

	if (n == 0) cout << "0";		//if not minterms then F is always 0;

	//CHECKING IF THE WHOLE KMAP IS 1

	string result[25];

	for (int i = 0; i < 25; i++) {
		result[i] = "0";
	}

	bool opt[2][4];
	bool fullyopt = false;
	int min = 1;
	int count = 0;		//counter for results

	for (int o = 0; o < 2; o++) { //INITIALIZING OPTIMIZATION ARRAY TO FALSE EXCEPT THE ZEROES ARE TRUE, since no need for opt
		for (int i = 0; i < 4; i++) {
			if (Kmap[o][i] == 0) opt[o][i] = true;
			else opt[o][i] = false;
		}
	}

	for (int k = 0; k < 2; k++) {
		for (int j = 0; j < 4; j++) {
			if (Kmap[k][j] < min) min = Kmap[k][j];
		}
	}

	if (min == 1) {		//THEN THE WHOLE KMAP IS 1 AND THE F MUST ALWAYS BE 1
		fullyopt = true;
		cout << "1\n";
	}
	
	
	//CHECKING IF A FULL ROW IS 1

	if (!fullyopt) {		//still need to optimize
		min = 1;

		for (int i = 0; i < 4; i++) {		//check 1st row
			if (Kmap[0][i] < min) min = Kmap[0][i];
		}

		if (min == 1) {		//This means the first row is all 1's
			for (int i = 0; i < 4; i++) opt[0][i] = true;
			result[count] = "C'";
			count++;
		}
		else {		//check second row
			min = 1;

			for (int i = 0; i < 4; i++) {		//check 1st row
				if (Kmap[1][i] < min) min = Kmap[1][i];
			}

			if (min == 1) {		//This means the second row is all 1's
				for (int i = 0; i < 4; i++) opt[1][i] = true;
				result[count] = "C";
				count++;
			}
		}

		fullyopt = true;	

		for (int c = 0; c < 2; c++) {			//start checking if all is optimized
			for (int j = 0; j < 4; j++) {
				if (opt[c][j] == false) {
					fullyopt = false;
					break;
				}
			}
			if (!fullyopt) break;
		}

		if (!fullyopt) {		//then we need to further optimize
			//CHECKING FOR SQUARES --> 4 possibilities
			if (Kmap[0][0] == 1) {		//check for 1st possibility
				if ((Kmap[0][1] == 1) && (Kmap[1][0] == 1) && (Kmap[1][1] == 1)) {
					opt[0][0] = true; opt[0][1] = true; opt[1][0] = true; opt[1][1] = true;		//setting the square to optimized
					result[count] = "A'";
					count++;
				}
			}

			if (Kmap[0][1] == 1) {		//check for 2nd possibility
				if ((Kmap[0][2] == 1) && (Kmap[1][1] == 1) && (Kmap[1][2] == 1)) {
					if ((opt[0][1] == false) || (opt[0][2] == false) || (opt[1][1] == false) || opt[1][2] == false) {	//so we do not double optimize
						opt[0][1] = true; opt[0][2] = true; opt[1][1] = true; opt[1][2] = true;		//setting the square to optimized
						result[count] = "B";
						count++;
					}
				}
			}

			if (Kmap[0][2] == 1) {		//check for 3rd possibility
				if ((Kmap[0][3] == 1) && (Kmap[1][2] == 1) && (Kmap[1][3] == 1)) {
					if ((opt[0][2] == false) || (opt[0][3] == false) || (opt[1][2] == false) || opt[1][3] == false) {	//so we do not double optimize
						opt[0][2] = true; opt[0][3] = true; opt[1][2] = true; opt[1][3] = true;		//setting the square to optimized
						result[count] = "A";
						count++;
					}
				}
			}

			if (Kmap[0][3] == 1) {		//check for 4th possibility
				if ((Kmap[0][0] == 1) && (Kmap[1][3] == 1) && (Kmap[1][0] == 1)) {
					if ((opt[0][3] == false) || (opt[0][0] == false) || (opt[1][3] == false) || opt[1][0] == false) {	//so we do not double optimize
						opt[0][3] = true; opt[0][0] = true; opt[1][3] = true; opt[1][0] = true;		//setting the square to optimized
						result[count] = "B'";
						count++;
					}
				}
			}

			fullyopt = true;

			for (int c = 0; c < 2; c++) {			//start checking if all is optimized
				for (int j = 0; j < 4; j++) {
					if (opt[c][j] == false) {
						fullyopt = false;
						break;
					}
				}
				if (!fullyopt) break;
			}

			if (!fullyopt) {		//then we need to further optimize
				//WE HAVE 12 POSSIBILITIES SO WE NEED TO CHECK ALL OF THEM

				if ((Kmap[0][0] == 1) && (Kmap[0][1])) {		//#1
					if ((opt[0][0] == false) || (opt[0][1] == false)) {
						opt[0][0] = true; opt[0][1] = true;
						result[count] = "A'C'";
						count++;
					}
				}

				if ((Kmap[0][1] == 1) && (Kmap[0][2])) {		//#2
					if ((opt[0][2] == false) || (opt[0][1] == false)) {
						opt[0][2] = true; opt[0][1] = true;
						result[count] = "BC'";
						count++;
					}
				}
				if ((Kmap[0][2] == 1) && (Kmap[0][3])) {		//#3
					if ((opt[0][2] == false) || (opt[0][3] == false)) {
						opt[0][2] = true; opt[0][3] = true;
						result[count] = "AC'";
						count++;
					}
				}
				if ((Kmap[0][0] == 1) && (Kmap[0][3])) {		//#4
					if ((opt[0][0] == false) || (opt[0][3] == false)) {
						opt[0][0] = true; opt[0][3] = true;
						result[count] = "B'C'";
						count++;
					}
				}
				if ((Kmap[1][0] == 1) && (Kmap[1][1])) {		//#5
					if ((opt[1][0] == false) || (opt[1][1] == false)) {
						opt[1][0] = true; opt[1][1] = true;
						result[count] = "A'C";
						count++;
					}
				}
				if ((Kmap[1][1] == 1) && (Kmap[1][2])) {		//#6
					if ((opt[1][1] == false) || (opt[1][2] == false)) {
						opt[1][1] = true; opt[1][2] = true;
						result[count] = "BC";
						count++;
					}
				}
				if ((Kmap[1][2] == 1) && (Kmap[1][3])) {		//#7
					if ((opt[1][2] == false) || (opt[1][3] == false)) {
						opt[1][2] = true; opt[1][3] = true;
						result[count] = "AC";
						count++;
					}
				}
				if ((Kmap[1][0] == 1) && (Kmap[1][3])) {		//#8
					if ((opt[1][0] == false) || (opt[1][3] == false)) {
						opt[1][0] = true; opt[1][3] = true;
						result[count] = "B'C";
						count++;
					}
				}
				if ((Kmap[0][0] == 1) && (Kmap[1][0])) {		//#9
					if ((opt[0][0] == false) || (opt[1][0] == false)) {
						opt[0][0] = true; opt[1][0] = true;
						result[count] = "A'B'";
						count++;
					}
				}

				if ((Kmap[1][1] == 1) && (Kmap[0][1])) {		//#10
					if ((opt[1][1] == false) || (opt[0][1] == false)) {
						opt[1][1] = true; opt[0][1] = true;
						result[count] = "A'B";
						count++;
					}
				}

				if ((Kmap[0][2] == 1) && (Kmap[1][2])) {		//#11
					if ((opt[0][2] == false) || (opt[1][2] == false)) {
						opt[0][2] = true; opt[1][2] = true;
						result[count] = "AB";
						count++;
					}
				}

				if ((Kmap[0][3] == 1) && (Kmap[1][3])) {		//#12
					if ((opt[0][3] == false) || (opt[1][3] == false)) {
						opt[0][3] = true; opt[1][3] = true;
						result[count] = "AB'";
						count++;
					}
				}

				fullyopt = true;

				for (int c = 0; c < 2; c++) {			//start checking if all is optimized
					for (int j = 0; j < 4; j++) {
						if (opt[c][j] == false) {
							fullyopt = false;
							break;
						}
					}
					if (!fullyopt) break;
				}

				if (!fullyopt) { //then we still need to further optimize
					//START CHECKING FOR THE SINGLES
					//WE HAVE 8 POSSIBILITIES
					if (opt[0][0] == false) {		//#1
						opt[0][0] = true;
						result[count] = "A'B'C'";
						count++;
					}

					if (opt[0][1] == false) {		//#2
						opt[0][1] = true;
						result[count] = "A'BC'";
						count++;
					}

					if (opt[0][2] == false) {		//#3
						opt[0][0] = true;
						result[count] = "ABC'";
						count++;
					}

					if (opt[0][3] == false) {		//#4
						opt[0][3] = true;
						result[count] = "AB'C'";
						count++;
					}

					if (opt[1][0] == false) {		//#5
						opt[1][0] = true;
						result[count] = "A'B'C";
						count++;
					}

					if (opt[1][1] == false) {		//#6
						opt[1][1] = true;
						result[count] = "A'BC";
						count++;
					}

					if (opt[1][2] == false) {		//#7
						opt[1][2] = true;
						result[count] = "ABC";
						count++;
					}

					if (opt[1][3] == false) {		//#8
						opt[1][3] = true;
						result[count] = "AB'C";
						count++;
					}

					fullyopt = true;

					for (int c = 0; c < 2; c++) {			//start checking if all is optimized
						for (int j = 0; j < 4; j++) {
							if (opt[c][j] == false) {
								fullyopt = false;
								break;
							}
						}
						if (!fullyopt) break;
					}
				}
			}
		}
	}

	if (fullyopt) {
		cout << "Function fully optimized\n";
	}
	else cout << "Not fully optimized but cannot optimize further\n";
	//Displaying the function

	int counter = 0;
	while (result[counter + 1] != "0") {
		cout << setw(3) << result[counter] << setw(3) << "+";
		counter++;
	}
	cout << result[counter] << "\n";

	system("pause");
	return 0;
}

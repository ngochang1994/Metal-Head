/* Thi Tran */
/* 825223653 */
/* C++ - METAL HEAD */

#include <iostream>
#include <math.h>

using namespace std;

#define FRET_MIN 1
#define FRET_MAX 24

class Guitar
{
public:
    Guitar()   // default constructor
    {

    }

    ~Guitar()   // destructor
    {

    }


    // Set the corresponding private field and verifies the input is between 1 and 24
    bool setFretBoardLength(const unsigned char numFrets)
    {
        numberOfFrets = numFrets;

        if (FRET_MIN < numberOfFrets && numberOfFrets < FRET_MAX)
            return true;
            return false;
    }

    // Returns the corresponding frequency in Hz for the given string and fret.
    // These use natural numbers, so the low E string shall be
    // string 1 and the high E string shall be 6
    double pitchAt(const unsigned char &stringNumber, const unsigned char &fret)
    {
        // Formula: Note x 2^(fret/12).
        // E: 82.41Hz
        // A: 110 Hz
        // D: 146.8 Hz
        // G: 196 Hz
        // B: 246.9 Hz
        // E: 329.6 Hz
        double standard_tune = 0;
        double factor = pow(2, ((double)fret)/12);

        switch ((int)stringNumber)
        {
            case 1: standard_tune = m_E_low; break;
            case 2: standard_tune = m_A; break;
            case 3: standard_tune = m_D; break;
            case 4: standard_tune = m_G; break;
            case 5: standard_tune = m_B; break;
            case 6: standard_tune = m_E_high; break;
        }

        return standard_tune * factor;
    }

    // Given the pitch, the method shall return a std::pair object with the string/fret combination
    // that comes closest to producing that pitch. There may be multiple solutions. The function
    // shall return the first it identifies
    std::pair<unsigned char, unsigned char> getStringAndFret( double pitch )
    {
        // Reverse pitch = Note x 2^(fret/12).
        // Iterate from fret 1->24, then calculate Note = pitch/(2^(fret/12))

        std::pair<unsigned char, unsigned char> str_fret_combo;
        double final_fret = 0;
        double final_note = 0;
        unsigned char final_string(0);

        for (int fret = 0; fret < FRET_MAX; ++fret)
        {
            double factor = pow(2, ((double)fret)/12);
            double note = pitch/factor;


            if (nearly_equal(note, m_E_low))
            {
                final_fret = fret;
                final_string = 1;
                break;
            }

            if (nearly_equal(note, m_A))
            {
                final_fret = fret;
                final_string = 2;
                break;
            }

            if (nearly_equal(note, m_D))
            {
                final_fret = fret;
                final_string = 3;
                break;
            }

            if (nearly_equal(note, m_G))
            {
                final_fret = fret;
                final_string = 4;
                break;
            }

            if (nearly_equal(note, m_B))
            {
                final_fret = fret;
                final_string = 5;
                break;
            }

            if (nearly_equal(note, m_E_high))
            {
                final_fret = fret;
                final_string = 6;
                break;
            }
        }

        str_fret_combo = std::make_pair(final_fret, final_string);
        return str_fret_combo;
    }

    // changes the tuning for an individual string.
    void tuneString(const unsigned char& string, const double& pitch )
    {
        switch ((int)string)
        {
            case 1: m_E_low = pitch; break;
            case 2: m_A = pitch; break;
            case 3: m_D = pitch; break;
            case 4: m_G = pitch; break;
            case 5: m_B = pitch; break;
            case 6: m_E_high = pitch; break;
        }
    }

    // Helper
    unsigned char getNumberOfFrets()
    {
        return numberOfFrets;
    }

    bool nearly_equal(double a, double b)
    {
        return std::abs(a-b)<0.1;
    }

    double get_string_pitch(const unsigned char& string)
    {
        switch ((int)string)
        {
            case 1: return m_E_low;
            case 2: return m_A;
            case 3: return m_D;
            case 4: return m_G;
            case 5: return m_B;
            case 6: return m_E_high;
        }
    }

private:
    unsigned char numberOfFrets;

    // tuning for individual string
    double m_E_low = 82.41;
    double m_A = 110;
    double m_D = 146.8;
    double m_G = 196;
    double m_B = 246.9;
    double m_E_high = 329.6;
};

// Test output
bool Test(Guitar& guitar, int stringNumber, int fret)
{
    std::cout << "String: " << stringNumber << "\t Fret: " << fret << "\t Pitch: " << guitar.pitchAt(stringNumber, fret) << endl;
    return true;
}

int main()
{
    Guitar guitar1;

// Display standard notes
    cout << "These are the standard notes: " << endl;
    Test(guitar1, 1, 0);   // E low
    Test(guitar1, 2, 0);   // A
    Test(guitar1, 3, 0);   // D
    Test(guitar1, 4, 0);   // G
    Test(guitar1, 5, 0);   // B
    Test(guitar1, 6, 0);   // E high

   cout << "..." << endl;

   // Test user input
   int stringNumber;
   int fret;
   cout << "Enter a string: ";
   cin >> stringNumber;
   cout << "Enter a fret: ";
   cin >> fret;
   cout << "The pitch is: " << guitar1.pitchAt(stringNumber, fret) << endl;
    return 0;
}

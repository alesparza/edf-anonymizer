# edf-anonymizer

edf-anonymizer is a C program that modifies some of the header contents of European Data Format (.edf) files, specifically the Local Patient Information section.  You can find the details of the EDF specification on the web [here](https://www.edfplus.info/specs/edf.html).

## Installation

### From Source

Clone this repository, then run `make all`.

### Pre-built binaries

Download the latest release from https://github.com/alesparza/edf-anonymizer/releases/latest.  Use the pre-compiled binaries for Linux and Windows (x86-64 architecture).

## Usage

```
edf-anonymizer -h|-H
# -h print a short help message
# -H print a more verbose help message
edf-anonymizer [-d|-s] [-r] [-i filename]
# -d use Detail Mode
# -s use Simple Mode (default)
# -r use Review mode (only print headers)
# -i provide input filename
```

### File names

The program prompts users for an input file name if the `-i` option is not used.  The output file appends `_deid` at the end.  E.g. `Test.edf` becomes `Test_deid.edf`.

The file extension must be `.edf`; rename the file if necessary.

### Detail Mode

Detail mode prompts four times, for patient ID, patient sex, patient date of birth, and patient name.  Avoid spaces in these fields (future update will convert spaces to underscores).

No entry by user (just presses `Enter`) converts to `X`.

Each subfield is separated by a space.

Data with more than 80 characters truncates.

EDF+ specification not enforced for dates (maybe in a future update).

### Simple Mode

Simple Mode allows users to provide a single input for the 80 characters in Local Patient Information section.  No guarantee that the user input follows the EDF+ specification.

### Review Mode

Review Mode stops after displaying the contents of the input file header.  In the other two modes, the program displays the contents of the output file header as a quick consistency check.

## Contributing

Pull requests are welcome. For major changes, please open an issue first
to discuss what you would like to change.

## License

[MIT](https://choosealicense.com/licenses/mit/)

""" This script writes a file that contains the name of all c files and header
    files in the 'app' directory.  The file if formatted to be used as the
    input to the 'uncrustify' tool. """

import os, itertools, glob

def multiple_file_types(*patterns):
    """ Returns an iterable that will yield filenames from the current
        directory that match any of the given patterns """
    return itertools.chain.from_iterable(glob.glob(pattern) for pattern in patterns)

if __name__ == "__main__":

    with open("_files_.txt", mode='wt') as outfile:
        os.chdir("./src")

        # iterate over filenames with our specified extention and write them out
        for filename in multiple_file_types("*.c", "*.h"):
            outfile.write(".\\src\\" + filename + '\n')

        os.chdir("./app")

        # iterate over filenames with our specified extention and write them out
        for filename in multiple_file_types("*.c", "*.h"):
            outfile.write(".\\src\\app\\" + filename + '\n')

        os.chdir("../os")

        # iterate over filenames with our specified extention and write them out
        for filename in multiple_file_types("*.c", "*.h"):
            outfile.write(".\\src\\os\\" + filename + '\n')

        os.chdir("../smf")

        # iterate over filenames with our specified extention and write them out
        for filename in multiple_file_types("*.c", "*.h"):
            outfile.write(".\\src\\smf\\" + filename + '\n')

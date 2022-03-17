#include <cassert>

#include <iostream>
#include <string>
#include <vector>

void usage(std::ostream& stream, const char *program_invocation_name = "align") {
    stream << "USAGE: " << program_invocation_name
           << " <delimiter>"
           << " [option...]"
           << '\n'

           << "OPTIONS:\n"
           << '\t' << "--add-space, -a        Add an extra space character before the delimiter if not already present" << '\n'
           << '\t' << "--find-last, -r        Align from last occurrence of <delimiter>, instead of first" << '\n';
}

int main(int argc, const char **argv) {
    assert(argc > 0);

    using namespace std;

    if (argc < 2) {
        usage(cerr, argv[0]);
        cerr << "ERROR: Not enough arguments" << endl;
        exit(1);
    }

    // if the C++ gods would be so kind as to zero-initialise this for us :)
    static struct {
        bool add_space;
        bool find_last;
        bool _invalid;
    } args;

    for (int i = 2; i < argc; i++) {
        string arg = string(argv[i]);

        if (arg == "-a" || arg == "--add-space") {
            args.add_space = true;
        } else if (arg == "-r" || arg == "--find-last") {
            args.find_last = true;
        } else {
            cerr << "ERROR: Unknown argument "
                 << '`' << arg << '`'
                 << '\n';
            args._invalid = true;
        }
    }

    if (args._invalid) {
        usage(cerr, argv[0]);
        exit(1);
    }

    const string delim = argv[1];

    vector<string> lines;

    for (string line; getline(cin, line);) {
        lines.push_back(line);
    }

    if (lines.empty()) {
        cerr << "ERROR: Empty input" << endl;
        exit(1);
    }

    int64_t max_idx = 0;
    for (string line : lines) {
        int64_t idx = args.find_last
                        ? line.rfind(delim)
                        : line. find(delim);
        if (idx >= max_idx) {
            max_idx = idx;
            if (args.add_space && !isspace(line[max_idx - 1])) {
                max_idx += 1;
            }
        }
    }

    for (string line : lines) {
        int64_t delim_idx = args.find_last
                                ? line.rfind(delim)
                                : line. find(delim);
        if (delim_idx < 0) {
            cout << line << '\n';
            continue;
        }

        string lpart = line.substr(0, delim_idx);
        string rpart = line.substr(delim_idx + delim.length());

        int64_t padlen = max_idx - delim_idx;
        assert(padlen >= 0);

        cout << lpart
             << string("").append(padlen, ' ')
             << delim
             << rpart
             << '\n';
    }

    return 0;
}

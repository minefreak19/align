#include <cassert>

#include <iostream>
#include <string>
#include <vector>

void usage(std::ostream& stream, const char *program_invocation_name = "align") {
    // TODO(#1): `-r` option, to align from last occurrence
    //  This should be as simple as using rfind instead of find

    // TODO: `--add-space` option
    //  This would add an extra space character before the delimiter
    //  on the longest line before the delimiter, if that line does not
    //  already have a space before the delimiter

    stream << "USAGE: " << program_invocation_name
           << " <delimiter>"
           << " [option...]"
           << '\n';
}

int main(int argc, const char **argv) {
    (void) argc;
    (void) argv;

    assert(argc > 0);

    using namespace std;

    if (argc < 2) {
        usage(cerr, argv[0]);
        cerr << "ERROR: Not enough arguments" << endl;
        exit(1);
    }

    for (int i = 2; i < argc; i++) {
        cerr << "ERROR: Unknown argument "
             << '`' << argv[i] << '`'
             << '\n';
    }

    if (argc > 2) {
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
        max_idx = max(max_idx, (int64_t) line.find(delim));
    }

    for (string line : lines) {
        int64_t delim_idx = line.find(delim);
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

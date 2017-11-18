#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

const char *session_path = "../sessions";
const char *error_no_dir = "The sessions folder is missing, please create it and try again<br>\n";
const char *error_is_file = "The sessions path appears to be a file, not a directory<br>\n";

void start_session(void)
{
    if (access(session_path, 0) == 0) {
        struct stat status;
        stat(session_path, &status);
        
        if (! (status.st_mode & S_IFDIR)) {
            std::cout << error_is_file;
        }
    } else {
        std::cout << error_no_dir; 
    }
}

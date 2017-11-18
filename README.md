# CGI library for C++ (WIP)

**cgee** is a small library to help create CGI pages using the C++ programming language. It will handle 
features like GET/POST requests, sessions, standard HTML headers, etc so you don't have to.

Eventually I'll turn it into a proper library, but for now you just need to include `cgee.h`.

## Example

```cpp
#include "cgee/cgee.h"

int main(void)
{
    init_cgee(); // mandatory
    start_session(); // (optional) if you want to use session storage

    // print a standard h1 tag to make sure the page is working
    std::cout << "<h1>Okay, it works</h1>\n";
    
    // in time I'll add a template engine, but for now just 
    // build a really basic page to make sure stuff is working
    const char *getname = "Please enter your name: "
        "<form action=\"\" method=\"post\"><input type=\"text\" value=\"\" name=\"user_name\">"
        "<br><input type=\"text\" name=\"age\"><br>\n"
        "<input type=\"submit\" name=\"submit\" value=\"Submit\"><br>\n"
        "</form><br>\n";

    // print it to stdout so it shows on the page
    std::cout << getname;

    // check for body parameters (POST requests)
    int bsz = body_params.size();
    if (bsz > 0) {
        std::cout << "Hello there, " << body_params["user_name"] << "<br>\n";

        if (body_params.count("age"))
            std::cout << "Number entered was " << body_params["age"] << "<br>\n";
    }

    // check for query parameters (GET requests)
    int qsz = query_params.size();
    if (qsz > 0) {
        std::cout << "We found " << qsz << " parameters<br>\n";
        std::cout << "Name is: " << query_params["name"] << "<br>\n";
    }

    return 0;
}
```

## Compiling

There are no external libraries, so you can just compile directly

```bash
g++ -o test.cgi test.cpp
```

This will obviously change when it becomes a proper library.

#include <string>
#include <vector>
#include <map>
#include <stdlib.h>


std::map<std::string, std::string> query_params;
std::map<std::string, std::string> body_params;

std::vector<std::string> tokenize(std::string const &in, char sep='&')
{
    std::string::size_type b = 0;
    std::vector<std::string> result;

    while ((b = in.find_first_not_of(sep, b)) != std::string::npos) {
        auto e = in.find_first_of(sep, b);
        result.push_back(in.substr(b, e-b));
        b = e;
    }
    return result;
}

void generate_body_params(void)
{
    int length = atoi(getenv("CONTENT_LENGTH"));
    if (length > 0) {
        char tmp[length+1];
        fread(tmp, length, 1, stdin);

        std::vector<std::string> c;
        std::vector<std::string> d;
        std::vector<std::string>::iterator it;
        std::vector<std::string>::iterator it2;

        c = tokenize(tmp);
        std::map <std::string, std::string> hashmap;

        int i = -1;
        for (it = c.begin(); it != c.end(); ++it) {
            d = tokenize(*it, '=');
            if (d.size() == 2)
                body_params[d[0]] = d[1];
        }
    }
}

void generate_query_params(void)
{
    const char *s = getenv("QUERY_STRING");
    
    if (s != NULL) {

        std::vector<std::string> c;
        std::vector<std::string> d;
        std::vector<std::string>::iterator it;
        std::vector<std::string>::iterator it2;

        c = tokenize(s);
        std::map <std::string, std::string> hashmap;
   
        int i = -1;
        for (it = c.begin(); it != c.end(); ++it) {
            d = tokenize(*it, '=');
            if (d.size() == 2)
                query_params[d[0]] = d[1];
        }
    }
}

void init_cgee(void)
{
    std::cout << "Content-Type: text/html\n\n";
    generate_body_params();
    generate_query_params();
}

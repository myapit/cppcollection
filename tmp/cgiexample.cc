#include <iostream>
#include <string>
#include <list>
#include <sstream>
#include <memory>

using namespace std;


const string c_ContentHeader = "Content-type: text/html\n\n";

    // ---- CONTENT LENGTH ----

    ///<Summary>
    /// The content length environment variable
    /// name
    ///</Summary>
    const string c_ContentLengthVariableName = "CONTENT_LENGTH";

    ///<Summary>
    /// Function to return the current requests
    /// content length
    ///</Summary>
    const int GetContentLength()
    {
        int l_result = 0;
        char* l_ContentLengthVariable = getenv(c_ContentLengthVariableName.c_str());
        if ( l_ContentLengthVariable != NULL )
        {
            l_result = atoi(l_ContentLengthVariable);
        }
        return l_result;

    }

    // ---- END CONTENT LENGTH ----


    // ---- GET CONTENT ----

    ///<Summary>
    /// Function to return the content
    ///</Summary>
    const list<string> GetContent()
    {
        list<string> l_result;

        // Now seek the content
        int l_ContentLength = GetContentLength();
        if ( l_ContentLength > 0 )
        {
            try
            {
                // Allocate a buffer for the information
                auto_ptr<char> l_Buffer (new char[l_ContentLength]);

                // Read the content sent into the buffer
                int l_bytesRead = fread (l_Buffer.get(), sizeof(char), l_ContentLength, stdin);

                // Check the data length
                if ( l_bytesRead == l_ContentLength )
                {                                        
                    // Convert the buffer to a string
                    stringstream l_stream (l_Buffer.get());

                    // Push the content as a string into the buffer
                    while ( !l_stream.eof() )
                    {
                        string l_item;
                        l_stream >> l_item;

                        l_result.push_back(l_item);
                    }
                }
            }
            catch (bad_alloc l_badAllocationException)
            {
                // TODO handle bad alloc
            }
        }

        return l_result;
    }

    // ---- END GET CONTENT ----


int main (int argc, char* argv[])
{
 cout << c_ContentHeader;
 cout << "<html><body>" << endl;
 cout << "The content Length is: " << GetContentLength() << "<br>" << endl;

 cout << "The Content is: <br><pre>" << endl;

 list<string> theContent = GetContent();
 for (list<string>::const_iterator itr = theContent.begin();
  itr != theContent.end();
  itr++)
 {
  cout << (*itr) << endl;
 }

 cout << "</pre><hr></body></html>" << endl;

 return 0;
}

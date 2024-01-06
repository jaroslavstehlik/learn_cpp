class string {
private:
    char* string_array_{ nullptr };
    int string_length{ 0 };

public:
    // constructors
    string();
    string(const char* value);

    // destructor
    ~string();

    // copy constructor
    string(const string& rhs);
    // move constructor
    string(string&& rhs) noexcept;
    // copy assignment operator
    string& operator=(const string& rhs);
    // move assignment operator
    string& operator=(string&& rhs) noexcept;

    const char* c_string() const;
    int length() const;
};
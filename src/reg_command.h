enum Registry_Value_Type
{
    DOUBLEWORD,
    STRINGZEROTERMINATED
};

//Simple write comman, haven't denoted how this works. 
struct Registry_command
{
    std::string reg_path;
    std::string reg_value_name;
    std::string reg_value_data;
    enum Registry_Value_Type reg_value_type;
    std::string completion_message;
};

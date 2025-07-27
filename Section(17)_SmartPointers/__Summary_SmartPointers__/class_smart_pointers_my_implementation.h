template <typename T>
class my_unique_ptr
{
private:
    T *raw_pointr;

public:
    my_unique_ptr(my_unique_ptr &copy) = delete;
    ~my_unique_ptr()
    {
        delete raw_pointr;    // deallocate data.
        raw_pointr = nullptr; // null the pointer
    }
}
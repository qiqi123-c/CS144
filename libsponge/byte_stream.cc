#include "byte_stream.hh"

// Dummy implementation of a flow-controlled in-memory byte stream.

// For Lab 0, please replace with a real implementation that passes the
// automated checks run by `make check_lab0`.

// You will need to add private members to the class declaration in `byte_stream.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

ByteStream::ByteStream(const size_t capacity) { _capacity = capacity; }

//尽量多写，返回写入的值
size_t ByteStream::write(const string &data) {
    if (_end) return 0;
    size_t t = min(data.size(), _capacity - _q.size());
    for (size_t i=0;i<t;i++)
    {
        _q.push_back(data[i]);
    }
    _write_num += t;
    return t;
}

//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len) const {
    size_t t = min(_q.size(),len);
    return string(_q.begin(),_q.begin()+t);
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) { 
    size_t t = min(_q.size(),len);
    _read_num += t;
    for (size_t i=0;i<t;i++)
        _q.pop_front();
    return;
 }

//! Read (i.e., copy and then pop) the next "len" bytes of the stream
//! \param[in] len bytes will be popped and returned
//! \returns a string
std::string ByteStream::read(const size_t len) {
    string s = this->peek_output(len);
    this->pop_output(len);
    return s;
}

//结束输入
void ByteStream::end_input() {
    _end = true;
    return;
}

//判断是否结束输入状态
bool ByteStream::input_ended() const { return _end; }

//现在最多可以从buffer读出的数量
size_t ByteStream::buffer_size() const { return _q.size(); }

//是否为空
bool ByteStream::buffer_empty() const { return _q.empty(); }

//是否到达结尾
bool ByteStream::eof() const { return _end&&_q.empty(); }

size_t ByteStream::bytes_written() const { return _write_num; }

size_t ByteStream::bytes_read() const { return _read_num; }

size_t ByteStream::remaining_capacity() const { return _capacity - _q.size(); }

//
// Created by whaim on 16-4-8.
//

#ifndef XESTCORE_MESSAGEBUFFER_H
#define XESTCORE_MESSAGEBUFFER_H

#include "Define.h"
#include <vector>
#include <cstring>

class MessageBuffer
{
    typedef std::vector<uint8>::size_type size_type;

public:
    MessageBuffer() : _wpos(0), _rpos(0), _storage()
    {
        _storage.resize(4096);
    }

    explicit MessageBuffer(std::size_t initialSize) : _wpos(0), _rpos(0), _storage()
    {
        _storage.resize(initialSize);
    }

    MessageBuffer(MessageBuffer const& right) : _wpos(right._wpos), _rpos(right._rpos), _storage(right._storage)
    {
    }

    MessageBuffer(MessageBuffer&& right) : _wpos(right._wpos), _rpos(right._rpos), _storage(right.Move()) { }

    //重置读写坐标
    void Reset()
    {
        _wpos = 0;
        _rpos = 0;
    }

    //重置空间大小
    void Resize(size_type bytes)
    {
        _storage.resize(bytes);
    }

    //获取基地址
    uint8* GetBasePointer() { return _storage.data(); }
    //获取读指针
    uint8* GetReadPointer() { return GetBasePointer() + _rpos; }
    //获取写指针
    uint8* GetWritePointer() { return GetBasePointer() + _wpos; }
    //读完成
    void ReadCompleted(size_type bytes) { _rpos += bytes; }
    //写完成
    void WriteCompleted(size_type bytes) { _wpos += bytes; }
    //获取可读取大小
    size_type GetActiveSize() const { return _wpos - _rpos; }
    //获取剩余空间
    size_type GetRemainingSpace() const { return _storage.size() - _wpos; }
    //获取总空间大小
    size_type GetBufferSize() const { return _storage.size(); }

    // Discards inactive data
    //丢弃已读取空间
    void Normalize()
    {
        if (_rpos)
        {
            if (_rpos != _wpos)
                memmove(GetBasePointer(), GetReadPointer(), GetActiveSize());
            _wpos -= _rpos;
            _rpos = 0;
        }
    }

    // Ensures there's "some" free space, make sure to call Normalize() before this
    //如果没有空间则扩容
    void EnsureFreeSpace()
    {
        // resize buffer if it's already full
        if (GetRemainingSpace() == 0)
            _storage.resize(_storage.size() * 3 / 2);
    }
    //写入
    void Write(void const* data, std::size_t size)
    {
        if (size)
        {
            memcpy(GetWritePointer(), data, size);
            WriteCompleted(size);
        }
    }

    std::vector<uint8>&& Move()
    {
        _wpos = 0;
        _rpos = 0;
        return std::move(_storage);
    }

    MessageBuffer& operator=(MessageBuffer const& right)
    {
        if (this != &right)
        {
            _wpos = right._wpos;
            _rpos = right._rpos;
            _storage = right._storage;
        }

        return *this;
    }

    MessageBuffer& operator=(MessageBuffer&& right)
    {
        if (this != &right)
        {
            _wpos = right._wpos;
            _rpos = right._rpos;
            _storage = right.Move();
        }

        return *this;
    }

private:
    size_type _wpos;  //当前写入位置
    size_type _rpos;  //当前读取位置
    std::vector<uint8> _storage;  //buffer 数据存储方式
};

#endif //XESTCORE_MESSAGEBUFFER_H

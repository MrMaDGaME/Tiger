/**
 ** \file type/builtin-types.hh
 ** \brief The classes Int, String, Void.
 */
#pragma once

#include <misc/singleton.hh>
#include <type/fwd.hh>
#include <type/type.hh>

namespace type
{
    class Int: public misc::Singleton<Int>, public Type
    {
        friend class Singleton<Int>;

    public:
        void accept(ConstVisitor& v) const override;
        void accept(Visitor& v) override;

    private:
        Int() = default;
    };

    class String : public misc::Singleton<String>, public Type
    {
        friend class Singleton<String>;

    public:
        void accept(ConstVisitor& v) const override;
        void accept(Visitor& v) override;

    private:
        String() = default;
    };

    class Void : public misc::Singleton<Void>, public Type
    {
        friend class Singleton<Void>;

    public:
        void accept(ConstVisitor& v) const override;
        void accept(Visitor& v) override;

    private:
        Void() = default;
    };
} // namespace type

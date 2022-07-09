#pragma once

#include <vector>
#include "board.h"

namespace sequence {
    class sequence {
    public:
        virtual int next_value() = 0;
        virtual bool has_next() = 0;
        virtual const char* name() = 0;
    };

    class random : public sequence {
    public:
        random();

        int next_value() final;
        bool has_next() final;
        const char* name() final {
            return "random";
        }

    private:
        std::vector<int> values;
    };

    class incremental : public sequence {
    public:
        int next_value() final;
        bool has_next() final;
        const char* name() final {
            return "incremental";
        }

    private:
        int current = 0;
    };
}

namespace difficulty {
    class difficulty {
    public:
        virtual int line_lower_bound() = 0;
        virtual int max_givens() = 0;
        virtual int min_givens() = 0;
    };

    class very_easy : public difficulty {
    public:
        int line_lower_bound() final
        {
            return 5;
        }

        int max_givens() final
        {
            return 65;
        }

        int min_givens() final
        {
            return 50;
        }
    };

    class easy : public difficulty {
    public:
        int line_lower_bound() final
        {
            return 4;
        }

        int max_givens() final
        {
            return 49;
        }

        int min_givens() final
        {
            return 36;
        }
    };

    class medium : public difficulty {
    public:
        int line_lower_bound() final
        {
            return 3;
        }

        int max_givens() final
        {
            return 35;
        }

        int min_givens() final
        {
            return 32;
        }
    };

    class hard : public difficulty {
    public:
        int line_lower_bound() final
        {
            return 2;
        }

        int max_givens() final
        {
            return 31;
        }

        int min_givens() final
        {
            return 28;
        }
    };

    class very_hard : public difficulty {
    public:
        int line_lower_bound() final
        {
            return 0;
        }

        int max_givens() final
        {
            return 27;
        }

        int min_givens() final
        {
            return 22;
        }
    };
}

class digger {
public:
    void dig(board *board, sequence::sequence* sequence, difficulty::difficulty* difficulty);
};

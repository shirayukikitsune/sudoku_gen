/*
   Copyright 2022 Bruno Rodrigues Ferreira

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

   http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

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
        virtual const char* name() = 0;
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

        const char* name() final
        {
            return "very easy";
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

        const char* name() final
        {
            return "easy";
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

        const char* name() final
        {
            return "medium";
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

        const char* name() final
        {
            return "hard";
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

        const char* name() final
        {
            return "very hard";
        }
    };
}

class digger {
public:
    void dig(board *board, sequence::sequence* sequence, difficulty::difficulty* difficulty);
};

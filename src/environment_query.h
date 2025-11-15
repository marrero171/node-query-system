#pragma once
#include "query_result.h"
#include <godot_cpp/classes/node.hpp>
#include <vector>
using std::vector;

namespace godot
{
    class CEnvironmentQuery : public Node
    {
        GDCLASS(CEnvironmentQuery, Node)

    protected:
        static void _bind_methods();

    public:
        CEnvironmentQuery();
        ~CEnvironmentQuery();

        void set_use_debug_shapes(const bool use_debug);
        bool get_use_debug_shapes() const;

        Ref<CQueryResult> request_query();

    private:
        bool use_debug_shapes;
        vector<CQueryItem> query_items;
    };

}
#include "generator_grid_shape3d.h"
Dictionary cast_ray_projection(Vector3 start_pos, Vector3 end_pos, Array exclusions);

void godot::CGeneratorGridShape3D::_bind_methods()
{
}

godot::CGeneratorGridShape3D::CGeneratorGridShape3D()
{
}

godot::CGeneratorGridShape3D::~CGeneratorGridShape3D()
{
}

double godot::CGeneratorGridShape3D::get_grid_half_size() const
{
    return grid_half_size;
}

void godot::CGeneratorGridShape3D::set_grid_half_size(double size)
{
    grid_half_size = size;
}

double godot::CGeneratorGridShape3D::get_space_between() const
{
    return space_between;
}

void godot::CGeneratorGridShape3D::set_space_between(double space)
{
    space_between = space;
}

CQueryContext3D *godot::CGeneratorGridShape3D::get_generate_around() const
{
    return generate_around;
}

void godot::CGeneratorGridShape3D::set_generate_around(CQueryContext3D *context)
{
    generate_around = context;
}

bool godot::CGeneratorGridShape3D::get_use_vertical_projection() const
{
    return use_vertical_projection;
}

void godot::CGeneratorGridShape3D::set_use_vertical_projection(bool use)
{
    use_vertical_projection = use;
}

double godot::CGeneratorGridShape3D::get_project_down() const
{
    return project_down;
}

void godot::CGeneratorGridShape3D::set_project_down(double project)
{
    project_down = project;
}

double godot::CGeneratorGridShape3D::get_project_up() const
{
    return project_up;
}

void godot::CGeneratorGridShape3D::set_project_up(double project)
{
    project_up = project;
}

double godot::CGeneratorGridShape3D::get_post_projection_vertical_offset() const
{
    return post_projection_vertical_offset;
}

void godot::CGeneratorGridShape3D::set_post_projection_vertical_offset(double offset)
{
    post_projection_vertical_offset = offset;
}

int godot::CGeneratorGridShape3D::get_projection_collision_mask() const
{
    return projection_collision_mask;
}

void godot::CGeneratorGridShape3D::set_projection_collision_mask(int mask)
{
    projection_collision_mask = mask;
}

void godot::CGeneratorGridShape3D::perform_generation(vector<CQueryItem> query_item_list)
{
    int grid_size = std::round(grid_half_size * 2 / space_between) + 1;
    Array contexts = generate_around->get_context();

    for (Variant context : contexts)
    {
        Vector3 starting_pos;
        if (context.get_type() == Variant::VECTOR3)
            starting_pos = context;
        else
        {
            Node3D *current_context = Object::cast_to<Node3D>(context);
            starting_pos = current_context->get_global_position();
        }
        starting_pos.x -= grid_half_size;
        starting_pos.z -= grid_half_size;

        for (int z = 0; z < grid_size; z++)
        {
            for (int x = 0; x < grid_size; x++)
            {
                double pos_x = starting_pos.x + (x * space_between);
                double pos_z = starting_pos.z + (z * space_between);

                if (!use_vertical_projection)
                {
                    query_item_list.push_back(CQueryItem(Vector3(pos_x, starting_pos.y, pos_z)));
                    continue;
                }

                Vector3 ray_pos = Vector3(pos_x, starting_pos.y, pos_z);
                Dictionary ray_result = cast_ray_projection(
                    ray_pos + (Vector3(0, 1, 0) * project_up),
                    ray_pos + (Vector3(0, -1, 0) * project_down), contexts);

                if (!ray_result.is_empty())
                {

                    Vector3 casted_position = (Vector3)ray_result.get("position", Vector3());
                    // TODO: Get the collider also
                    query_item_list.push_back(
                        CQueryItem(casted_position + Vector3(0, 1, 0) * post_projection_vertical_offset));
                }
            }
        }
    }
}

Dictionary cast_ray_projection(Vector3 start_pos, Vector3 end_pos, Array exclusions)
{
    return Dictionary();
}
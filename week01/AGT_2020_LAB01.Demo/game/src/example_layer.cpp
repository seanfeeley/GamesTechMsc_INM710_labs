#include "example_layer.h"
#include "platform/opengl/gl_shader.h"

#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp>
#include "engine/events/key_event.h"

example_layer::example_layer()
	:m_2d_camera(-1.6f, 1.6f, -0.9f, 0.9f),
	m_3d_camera((float)engine::application::window().width(), (float)engine::application::window().height())
{
	// hide the mouse and lock it inside the window
	//engine::application::window().hide_mouse_cursor();

	float radius_r = 3.f;
	float radius_g = 2.f;
	float radius_b = 1.f;
	uint32_t stacks = 12;
	uint32_t slices = 12;

	m_position_r = 0.0f;
	m_position_g = 0.0f;
	m_position_b = 0.0f;
	m_speed = 5.0f;

	engine::ref<engine::sphere> m_sphere_shape_r = engine::sphere::create(stacks, slices, radius_r);
	engine::ref<engine::sphere> m_sphere_shape_g = engine::sphere::create(stacks, slices, radius_g);
	engine::ref<engine::sphere> m_sphere_shape_b = engine::sphere::create(stacks, slices, radius_b);
	engine::game_object_properties sphere_props_r;
	engine::game_object_properties sphere_props_g;
	engine::game_object_properties sphere_props_b;
	sphere_props_r.meshes = { m_sphere_shape_r->mesh() };
	sphere_props_g.meshes = { m_sphere_shape_g->mesh() };
	sphere_props_b.meshes = { m_sphere_shape_b->mesh() };
	sphere_props_r.position = { 0.0f, 1.5f, -10.0f };
	sphere_props_g.position = { 0.0f, 1.5f, -10.0f };
	sphere_props_b.position = { 0.0f, 1.5f, -10.0f };

	m_sphere_r = engine::game_object::create(sphere_props_r);
	m_sphere_g = engine::game_object::create(sphere_props_g);
	m_sphere_b = engine::game_object::create(sphere_props_b);
}

example_layer::~example_layer() {}

void example_layer::on_update(const engine::timestep& time_step){

	m_position_r += m_speed * time_step;
	if (m_position_r > 10.0f || m_position_r < -10)
		m_position_r = -m_position_r;
	m_position_g += m_speed * time_step;
	if (m_position_g > 10.0f || m_position_g < -10)
		m_position_g = -m_position_g;
	m_position_b += m_speed * time_step;
	if (m_position_b > 10.0f || m_position_b < -10)
		m_position_b = -m_position_b;
}

void example_layer::on_render()
{
	engine::render_command::clear_color({ 0.0f, 0.0f, 0.0f, 1.0f });
	engine::render_command::clear();
	
	const auto colour_shader_r = engine::renderer::shaders_library()->get("colour");
	engine::renderer::begin_scene(m_3d_camera, colour_shader_r);

	glm::vec4 sphere_colour_r = glm::vec4(.8f, 0.1f, .1f, 1.f);
	glm::vec3 sphere_position_r = glm::vec3(m_position_r, m_position_b, -20.0f);

	std::dynamic_pointer_cast<engine::gl_shader>(colour_shader_r)->set_uniform("a_color", sphere_colour_r);
	glm::mat4 transform_1_r = glm::translate(glm::mat4(1.0f), sphere_position_r);
	engine::renderer::submit(colour_shader_r, m_sphere_r->meshes().at(0), transform_1_r);





	const auto colour_shader_g = engine::renderer::shaders_library()->get("colour");
	engine::renderer::begin_scene(m_3d_camera, colour_shader_g);

	glm::vec4 sphere_colour_g = glm::vec4(.1f, 0.8f, .1f, 1.f);
	glm::vec3 sphere_position_g = glm::vec3(0, m_position_g, -15.0f);

	std::dynamic_pointer_cast<engine::gl_shader>(colour_shader_g)->set_uniform("a_color", sphere_colour_g);
	glm::mat4 transform_1_g = glm::translate(glm::mat4(1.0f), sphere_position_g);
	engine::renderer::submit(colour_shader_g, m_sphere_g->meshes().at(0), transform_1_g);









	const auto colour_shader_b = engine::renderer::shaders_library()->get("colour");
	engine::renderer::begin_scene(m_3d_camera, colour_shader_b);

	glm::vec4 sphere_colour_b = glm::vec4(.1f, 0.1f, .8f, 1.f);
	glm::vec3 sphere_position_b = glm::vec3(m_position_b, 1.5f, -10.0f);

	std::dynamic_pointer_cast<engine::gl_shader>(colour_shader_b)->set_uniform("a_color", sphere_colour_b);
	glm::mat4 transform_1_b = glm::translate(glm::mat4(1.0f), sphere_position_b);
	engine::renderer::submit(colour_shader_b, m_sphere_b->meshes().at(0), transform_1_b);

	engine::renderer::end_scene();
}

void example_layer::on_event(engine::event& event)
{
	if (event.event_type() == engine::event_type_e::key_pressed)
	{
		auto& e = dynamic_cast<engine::key_pressed_event&>(event);
		if (e.key_code() == engine::key_codes::KEY_TAB)
		{
			engine::render_command::toggle_wireframe();
		}
		if (e.key_code() == engine::key_codes::KEY_UP)
		{
			m_speed = m_speed + 2.0f;
			// 10% faster
		}
		if (e.key_code() == engine::key_codes::KEY_DOWN)
		{
			m_speed = m_speed - 2.0f;
			// 10% slower
		}
		if (m_speed > 100.0f)
		{
			m_speed = 100.0f;
		}
		else if (m_speed < -100.0f)
		{
			m_speed = -100.0f;
		}
	}
}

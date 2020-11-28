#pragma once
#include <engine.h>

class example_layer : public engine::layer
{
public:
	example_layer();
	~example_layer();

	
	void on_render() override;
	void on_event(engine::event& event) override;
	void on_update(const engine::timestep& time_step) override;
private:

	engine::ref<engine::texture_2d>     m_skybox_texture{};
	engine::ref<engine::skybox>			m_skybox{};
	engine::ref<engine::game_object>	m_sphere_r;
	engine::ref<engine::game_object>	m_sphere_g;
	engine::ref<engine::game_object>	m_sphere_b;

	float m_position_r;
	float m_position_g;
	float m_position_b;
	float m_speed;

	engine::orthographic_camera       m_2d_camera;
	engine::perspective_camera        m_3d_camera;
};

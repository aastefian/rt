/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 12:21:37 by aanzieu           #+#    #+#             */
/*   Updated: 2017/10/04 14:56:26 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_H
# define GUI_H

# include "../../../includes/rt.h"

# define UNUSED(a) (void)a

# define MAX_VERTEX_MEMORY 1024 * 1024
# define MAX_ELEMENT_MEMORY 512 * 1024

# ifdef __APPLE__
#  define NK_SHADER_VERSION "#version 150\n"
# else
#  define NK_SHADER_VERSION "#version 300 es\n"
# endif

# define WINDOW_WIDTH 1540
# define WINDOW_HEIGHT 867

void			clear(struct nk_context *ctx, t_world *w);
void			ui_widget(struct nk_context *ctx, struct media *media,
				float height);
void			ui_header(struct nk_context *ctx, struct media *media,
				const char *str);
void			ui_widget_centered(struct nk_context *ctx,
				struct media *m, float h);
void			ui_widget_small_button(struct nk_context *ctx, struct media *m,
				float h);
void			ui_widget_special_mode(struct nk_context *ctx, struct media *m,
				float h);
int				ui_widget_value_infos(struct nk_context *ctx,
				struct media *media, double *value, char *title);
int				ui_widget_value_infos_cam(struct nk_context *ctx, double *value,
				char *title);
int				ui_slide_float_intensity(struct nk_context *ctx, double *value,
				char *title);
void			ui_slide_float_perlin(struct nk_context *ctx, t_perlin *p,
				double *value, char *title);
void			ui_slide_int_0_to_8(struct nk_context *ctx, t_world *w,
				int step, char *title);
void			ui_slide_float_0_to_1(struct nk_context *ctx,
				double *value, char *title);
void			ui_slide_float_0_to_2(struct nk_context *ctx,
				double *value, char *title);
void			text_float_left(struct nk_context *ctx, char *str, int w);

/*
** ===============================================================
**
**                         DELETE OBJECTS
**
**===============================================================
*/

void			remove_sphere(t_sphere **s, t_intersection *i, t_sphere *tmp);
void			remove_cone(t_cone **s, t_intersection *i);
void			remove_cylinder(t_cylinder **s, t_intersection *i);
void			remove_plane(t_plane **s, t_intersection *i);
void			remove_torus(t_torus **s, t_intersection *i);
void			remove_mobius(t_mobius **s, t_intersection *i);
void			remove_disk(t_disk **s, t_intersection *i);
void			remove_cube(t_cube **s, t_intersection *i);
void			remove_h_cube(t_h_cube **s, t_intersection *i);
void			remove_hyperboloid(t_hyperboloid **s, t_intersection *i);
void			remove_paraboloid(t_paraboloid **s, t_intersection *i);
void			remove_triangle(t_triangle **s, t_intersection *i);
void			remove_light(t_light **l, t_intersection *i);
int				mousepress_middle(struct nk_context *ctx, t_world *world,
				struct nk_vec2 pos);
int				mousepress_left(struct nk_context *ctx, t_world *world,
				struct nk_vec2 pos);

/*
** ===============================================================
**
**                          WINDOW POP UP
**
**===============================================================
*/

void			objects_param(struct nk_context *ctx, struct media *media,
				t_world *world);
void			scene_parameters(struct nk_context *ctx, struct media *media,
				t_world *world);
void			scene_parameters_next(struct nk_context *ctx,
				struct media *media, t_world *world);
void			draw_objects_button_3(struct nk_context *ctx,
				struct media *media, t_world *w);
void			scene_effects(struct nk_context *ctx, struct media *media,
				t_world *world);
void			scene_topbar(struct nk_context *ctx, struct media *media,
				t_world *world);
void			draw_topbar_add_objects(struct nk_context *c, struct media *m,
				t_world *w);
void			camera_control_bar(struct nk_context *ctx, struct media *m,
				t_world *w);
void			render_scene(struct nk_context *ctx, struct media *media,
				t_world *w);

/*
** ===============================================================
**
**                          DEVICE INIT
**
** ===============================================================
*/

void			device_shutdown(struct device *dev);
void			device_upload_atlas(struct device *dev, const void *image,
				int width, int height);
void			device_init(struct device *dev);
void			set_up_global_state(struct device *dev, GLfloat ortho[4][4]);
void			allocate_mouse(struct nk_context *ctx, GLFWwindow *win);
void			allocate_keys(struct nk_context *c, GLFWwindow *w);
void			delete_object(struct nk_context ctx, struct media media);
void			allocate_vertex_buffer_next(struct nk_context *ctx,
				struct device *dev, struct nk_convert_config config);
int				render_condition(struct nk_context *ctx, t_world *world);
void			reset_camera(t_world *world, int i);

/*
** ===============================================================
**
**                          OPENGL INIT
**
** ===============================================================
*/

void			defaut_opengl_state();
void			init_glfw_start(GLFWwindow **win, struct nk_context *ctx,
				t_screen *screen);
void			error_callback(int e, const char *d);
void			scroll_input(GLFWwindow *win, double u, double yoff);
void			text_input(GLFWwindow *win, unsigned int codepoint);
void			die(const char *fmt, ...);
struct nk_image	icon_load(const char *filename);
void			loading_media(struct media *media,
				struct nk_context *ctx, struct device *device);
void			device_draw(struct device *dev, struct nk_context *ctx,
				t_screen *screen, enum nk_anti_aliasing aa);
void			allocate_vertex_buffer(struct device *dev,
				enum nk_anti_aliasing aa, struct nk_context *ctx);
int				move_camera_render_next(struct nk_context *ctx, t_world *world);
int				key_press(struct nk_context *ctx, t_world *world);
void			sphere_informations(t_world *world, struct nk_context *ctx,
				struct media *media);
void			refresh_sphere(t_world *world, int i);
void			cone_informations(t_world *world, struct nk_context *ctx,
				struct media *media);
void			refresh_cone(t_world *world, int i);
void			cylinder_informations(t_world *world, struct nk_context *ctx,
				struct media *media);
void			refresh_cylinder(t_world *world, int i);
void			plane_informations(t_world *world, struct nk_context *ctx,
				struct media *media);
void			refresh_plane(t_world *world, int i);
void			torus_informations(t_world *world, struct nk_context *ctx,
				struct media *media);
void			refresh_torus(t_world *world, int i);
void			mobius_informations(t_world *world, struct nk_context *ctx,
				struct media *media);
void			refresh_mobius(t_world *world, int i);
void			disk_informations(t_world *world, struct nk_context *ctx,
				struct media *media);
void			refresh_disk(t_world *world, int i);
void			cube_informations(t_world *world, struct nk_context *ctx,
				struct media *media);
void			refresh_cube(t_world *world, int i);
void			h_cube_informations(t_world *world, struct nk_context *ctx,
				struct media *media);
void			refresh_h_cube(t_world *world, int i);
void			paraboloid_informations(t_world *world, struct nk_context *ctx,
				struct media *media);
void			refresh_paraboloid(t_world *world, int i);
void			hyperboloid_informations(t_world *world, struct nk_context *ctx,
				struct media *media);
void			refresh_hyperboloid(t_world *world, int i);
void			triangle_informations(t_world *world, struct nk_context *ctx,
				struct media *media);
void			refresh_triangle(t_world *world, int i);
void			light_informations(t_world *world, struct nk_context *ctx,
				struct media *media);
void			refresh_light(t_world *world, int i);
int				get_preset_info(t_perlin p);
int				move_object(struct nk_context *ctx, t_vec3d *pos,
				t_vec3d *normal);
int				move_object_without_norm(struct nk_context *ctx, t_vec3d *pos);
int				draw_color_picker(struct nk_context *ctx, t_color *o,
				t_world *world);
void			draw_chess_color(struct nk_context *ctx, struct media *m,
				t_world *world, t_color *c);
void			draw_choose_color(struct nk_context *ctx, t_world *world,
				t_color *c);
void			header_info(struct nk_context *ctx,
				struct nk_image img, char *n);
void			draw_apply_button(struct nk_context *c, struct media *m,
				t_world *w);
void			select_scene(struct nk_context *ctx, struct media *media,
				t_world *world, int img_active[5]);
void			select_your_file(struct nk_context *ctx, struct media *media,
				t_world *world, int img_active[5]);
void			press_launch(struct nk_context *ctx, t_world *world,
				int img_active[5]);
int				launch_xml_file(struct nk_context *ctx, t_world *world,
				char *xml);
void			draw_light_type(struct nk_context *c, struct media *m,
				t_world *w, t_light *light);
void			draw_p_presets(struct nk_context *c, struct media *m,
				t_world *w, t_perlin *perlin);
void			draw_infos_next(struct nk_context *c, struct media *m,
				t_perlin *perlin, t_world *w);

#endif

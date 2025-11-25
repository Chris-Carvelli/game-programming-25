// 
//

#ifndef ITU_ENTITY_STORAGE_HPP
#define ITU_ENTITY_STORAGE_HPP

#ifndef ITU_UNITY_BUILD
#include <SDL3/SDL.h>
#include <itu_lib_engine.hpp>
#endif

// NOTE: this is decided by the size of the `component_mask` type (Uint64).
//       DO NOT CHANGE THIS unless you also increase the size of the bitmask!
#define COMPONENTS_COUNT_MAX  64
// NOTE: this is decided by the size of the `tag_mask` tupe (Uint64).
//       DO NOT CHANGE THIS unless you also increase the size of the bitmask!
#define TAGS_COUNT_MAX        64

#define SYSTEMS_COUNT_MAX     64
#define SYSTEM_COMPONENTS_MAX  8
#define SYSTEM_TAGS_MAX        8
#define ENTITIES_COUNT_MAX 4096 * 4

#define ITU_ENTITY_ID_NULL { (Uint32)-1, (Uint32)-1 }

// unique identifier for an entity. This sould be treated as an opaque handle
struct ITU_EntityId
{
	Uint32 generation;
	Uint32 index;
};

typedef Uint8 ITU_ComponentType;
typedef Uint8 ITU_TagType;

// signature for a system-like update function
typedef void (*ITU_SystemUpdateFunction)(SDLContext* context, ITU_EntityId* entity_ids, int entity_ids_count);

// signature for a component debug UI render function
typedef void (*ITU_ComponendDebugUIRender)(SDLContext* context, void* data);

struct ITU_SystemDef
{
	const char* name;
	ITU_SystemUpdateFunction fn_update;
	Uint64 component_mask;
	Uint64 tag_mask;
};

#define register_component(T) ITU_ComponentType ITU_COMPONENT_TYPE_##T = -1; const char* ITU_COMPONENT_NAME_##T = #T;
#define enable_component(T) itu_sys_estorage_add_component_pool(sizeof(T), ENTITIES_COUNT_MAX, &ITU_COMPONENT_TYPE_##T, ITU_COMPONENT_NAME_##T)

#define add_component_debug_ui_render(T, fn_debug_ui_render) itu_sys_estorage_add_component_debug_ui_render(ITU_COMPONENT_TYPE_##T, ITU_COMPONENT_NAME_##T, fn_debug_ui_render);

#define entity_get_data(id, T) (T*)itu_entity_data_get((id), ITU_COMPONENT_TYPE_##T)

#define add_system(fn_update, component_mask, tag_mask) itu_sys_estorage_add_system({ #fn_update, fn_update, component_mask, tag_mask })
#define entity_add_component(id, T, value) { type_check_struct(T, value); itu_entity_component_add((id), ITU_COMPONENT_TYPE_##T, ITU_COMPONENT_NAME_##T, &value); }
#define entity_remove_component(id, T, value) { type_check_struct(T, value); itu_entity_component_remove((id), ITU_COMPONENT_TYPE_##T, ITU_COMPONENT_NAME_##T); }

#define component_mask(T) (1ull << ITU_COMPONENT_TYPE_##T)
#define component_type(T) ITU_COMPONENT_TYPE_##T

#define tag_mask(tag) (1ull << tag)
#define set_tag_debug_name(tag, name) itu_sys_estorage_tag_set_debug_name(tag, name);


// register default components
register_component(Transform)
register_component(Sprite)
register_component(PhysicsData)
register_component(PhysicsStaticData)
register_component(ShapeData)
register_component(Transform3D)
register_component(MeshComponent)
register_component(CameraComponent)

void itu_sys_estorage_init(int starting_entities_count, bool enable_standard_components);
void itu_sys_estorage_clear_all_entities();
int  itu_sys_estorage_query_entities(Uint64 component_mask, Uint64 tag_mask);
void itu_sys_estorage_component_sort_data(ITU_ComponentType component_type, SDL_CompareCallback fn_compare);
void itu_sys_estorage_add_system(ITU_SystemDef system_def);
void itu_sys_estorage_set_systems(ITU_SystemDef* systems, int systems_count);
void itu_sys_estorage_systems_update(SDLContext* context);

void itu_sys_estorage_tag_set_debug_name(int tag, const char* tag_debug_name);
void itu_sys_estorage_debug_render(SDLContext* context);

ITU_EntityId itu_entity_create();
void         itu_entity_set_debug_name  (ITU_EntityId id, const char* debug_name);
const char*  itu_entity_get_debug_name (ITU_EntityId id);
bool         itu_entity_equals          (ITU_EntityId a, ITU_EntityId b);
bool         itu_entity_is_valid        (ITU_EntityId id);
void         itu_entity_idcaret_to_stringid  (ITU_EntityId id, char* buffer, int max_len);
void*        itu_entity_data_get        (ITU_EntityId id, ITU_ComponentType component_type);
void         itu_entity_tag_add         (ITU_EntityId id, ITU_TagType tag);
void         itu_entity_tag_remove      (ITU_EntityId id, ITU_TagType tag);
bool         itu_entity_tag_has         (ITU_EntityId id, ITU_TagType tag);
void         itu_entity_component_add   (ITU_EntityId id, ITU_ComponentType type, const char* name, void* in_data_copy);
void         itu_entity_component_remove(ITU_EntityId id, ITU_ComponentType type, const char* name);
void         itu_entity_destroy         (ITU_EntityId id);

void itu_debug_ui_widget_entityid(const char* label, ITU_EntityId id);
void itu_debug_ui_widget_entityid_tablerow(ITU_EntityId id);

#endif // ITU_ENTITY_STORAGE_HPP

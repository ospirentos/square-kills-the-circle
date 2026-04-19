#include "lua_bridge.hpp"

extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

namespace LuaBridge {

// Yardımcı: stack'teki table'dan float alanı okur, stack'i değiştirmez.
// [Lua stack mantığı] lua_getfield: table[-1]'den "key"i alır, stack'e push eder.
//                    lua_tonumber:  stack tepesini okur (pop etmez).
//                    lua_pop:       stack tepesini atar.
static float getFloat(lua_State* L, const char* key) {
    lua_getfield(L, -1, key);           // stack: [..., table, value]
    float val = (float)lua_tonumber(L, -1);
    lua_pop(L, 1);                      // stack: [..., table]
    return val;
}

// [Ne yapıyor] Lua dosyasını çalıştırır, return {} tablosunu okur, EntityDef olarak döner.
// [Dikkat] scriptPath proje kök dizinine göre göreceli — oyun proje kökünden çalıştırılmalı.
//          Doğru: ./build/square-kills-the-circle   Yanlış: cd build && ./square-kills-the-circle
EntityDef load(const char* scriptPath) {
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    // Dosyayı çalıştır; return değeri (tablo) stack tepesine oturur: stack: [table]
    luaL_dofile(L, scriptPath);

    EntityDef result{};
    result.hp             = getFloat(L, "hp");
    result.speed          = getFloat(L, "speed");
    result.damage         = getFloat(L, "damage");
    result.radius         = getFloat(L, "radius");
    result.attackRange    = getFloat(L, "attack_range");
    result.attackCooldown = getFloat(L, "attack_cooldown");

    // color tablosuna gir: stack: [table, color_table]
    lua_getfield(L, -1, "color");
    result.color = Color{
        (unsigned char)(int)getFloat(L, "r"),
        (unsigned char)(int)getFloat(L, "g"),
        (unsigned char)(int)getFloat(L, "b"),
        255
    };
    lua_pop(L, 1); // color_table'ı pop et: stack: [table]

    lua_close(L);
    return result;
}

} // namespace LuaBridge

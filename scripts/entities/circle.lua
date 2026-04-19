-- Daire entity tanımı
-- Hızlı ama düşük HP'li — kalabalık gruplar halinde etkili

return {
    hp     = 80,
    speed  = 140,
    damage = 10,
    radius = 16,
    attack_range   = 42,
    attack_cooldown = 0.8,
    color  = { r = 100, g = 180, b = 255 },

    on_spawn = function(self)
    end,

    on_attack = function(self, target)
        target.hp = target.hp - self.damage
    end,

    on_death = function(self)
    end
}

-- Üçgen entity tanımı
-- Orta hız, orta hasar — dengeli savaşçı

return {
    hp     = 110,
    speed  = 100,
    damage = 18,
    radius = 19,
    attack_range   = 24,
    attack_cooldown = 1.0,
    color  = { r = 120, g = 220, b = 120 },

    on_spawn = function(self)
    end,

    on_attack = function(self, target)
        target.hp = target.hp - self.damage
    end,

    on_death = function(self)
    end
}

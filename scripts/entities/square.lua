-- Kare entity tanımı
-- Yavaş ama yüksek HP ve hasar — tank rolü

return {
    hp     = 160,
    speed  = 70,
    damage = 25,
    radius = 22,
    attack_range   = 28,
    attack_cooldown = 1.4,
    color  = { r = 255, g = 120, b = 80 },

    on_spawn = function(self)
    end,

    on_attack = function(self, target)
        target.hp = target.hp - self.damage
    end,

    on_death = function(self)
    end
}

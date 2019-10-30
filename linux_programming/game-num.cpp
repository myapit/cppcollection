#include <cstdio>
#include <random>

int main(int argc, char* argv[])
{

    double dt = 0.01;

    double sim_time = 120.0;

    int player_level = 29;
    int player_weapon_skill = 145;
    double player_crit = 4.5 / 100.0;
    double player_attack_power = 243;

    int enemy_level = 29;
    double enemy_block_value = 10.0;
    double enemy_armor       = 2293.0;

    double armor_dmg_reduction = enemy_armor / (enemy_armor + 400 + 85 * player_level);

    // Weapon info (Strike of the Hydra)
    double weapon_speed = 3.3;
    double weapon_dmg_low  = 67.0;
    double weapon_dmg_high = 102.0;

    size_t num_attack_stats = 6;
    double white_attack_stats[] = {
         /* Miss     */ 0.05 + (player_weapon_skill - player_level * 5) * 0.04,
         /* Dodge    */ 0.05,
         /* Parry    */ 0.05,
         /* Glancing */ 0.00,
         /* Block    */ 0.00,
         /* Critical */ player_crit
    };

    double yellow_attack_stats[] = {
         /* Miss     */ 0.05 + (player_weapon_skill - player_level * 5) * 0.04,
         /* Dodge    */ 0.05,
         /* Parry    */ 0.05,
         /* Glancing */ 0.00,
         /* Block    */ 0.00,
         /* Critical */ player_crit
    };

    double white_attack_table[num_attack_stats];
    double yellow_attack_table[num_attack_stats];
    white_attack_table[0]  = white_attack_stats[0];
    yellow_attack_table[0] = yellow_attack_stats[0];
    for(size_t i = 1; i < num_attack_stats; ++i)
    {
        white_attack_table[i]  = white_attack_table[i - 1] + white_attack_stats[i];
        yellow_attack_table[i] = yellow_attack_table[i - 1] + yellow_attack_stats[i];
    }

    std::mt19937_64 prng(13);
    std::uniform_real_distribution<double> rand;

    double t = 0.0;

    double total_dmg = 0.0;

    bool auto_attack_enabled = true;
    double auto_attack_start = 0.0;
    while(t < sim_time)
    {
        if(auto_attack_enabled && t - auto_attack_start >= weapon_speed)
        {
            //Attack
            double time_attack = auto_attack_start + weapon_speed;
            double attack_type_roll = rand(prng);
            if(attack_type_roll < white_attack_table[0])
            {
                printf("%.2f miss:\n", time_attack);
            }
            else if(attack_type_roll < white_attack_table[1])
            {
                printf("%.2f dodge:\n", time_attack);
            }
            else if(attack_type_roll < white_attack_table[2])
            {
                printf("%.2f parry:\n", time_attack);
            }
            else
            {
                double weapon_base_dmg = (weapon_dmg_low + rand(prng) * (weapon_dmg_high - weapon_dmg_low)) + (player_attack_power / 14.0) * weapon_speed;
                weapon_base_dmg *= (1.0 - armor_dmg_reduction);

                if(attack_type_roll < white_attack_table[3])
                {
                    // @todo: Handle glancing blows correctly
                    weapon_base_dmg *= 0.1;
                    printf("%.2f glancing: %f\n", time_attack, weapon_base_dmg);
                }
                else if(attack_type_roll < white_attack_table[4])
                {
                    weapon_base_dmg -= enemy_block_value;
                    printf("%.2f block:    %f(%f blocked)\n", time_attack, weapon_base_dmg, enemy_block_value);
                }
                else if(attack_type_roll < white_attack_table[5])
                {
                    weapon_base_dmg *= 2;
                    printf("%.2f critical: %f\n", time_attack, weapon_base_dmg);
                }
                else
                {
                    printf("%.2f hit:      %f\n", time_attack, weapon_base_dmg);
                }

                total_dmg += weapon_base_dmg;
            }

            auto_attack_start = time_attack;
        }

        t += dt;
    }

    printf("Total damage: %.2f, DPS: %.2f\n", total_dmg, total_dmg / sim_time);

    return 0;
}

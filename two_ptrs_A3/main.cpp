#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

int main()
{
    long long n;
    long long des_mood_p;

    cin >> n >> des_mood_p;
    vector<long long> nums(n);

    long long answer_position = 0;
    long long answer_quant = des_mood_p + 1;

    for (long long i = 0; i < n; ++i) {
        cin >> nums[i]; }

    // находим сумму получаемого счастья за весь плейлист
    long long sum_of_elems = accumulate(nums.begin(), prev(nums.end()), 0);
    // считаем кол-во полных проходов по плейлисту для получения заданного уровня
    long long cycle = des_mood_p / sum_of_elems;
    // кол-во полученного счастья после прослушивания плейлиста по кругу
    long long quant_happ = cycle * sum_of_elems;
    long long quant_music = cycle * nums.size();

    for (long long i = 0; i < nums.size(); ++i)
    {
        long long it = i;
        long long cur_happ = quant_happ;
        long long cur_quant_music = quant_music;

        while ((cur_happ < des_mood_p) && (it < nums.size()))
        {
            cur_happ += nums[it];
            cur_quant_music += 1;
            ++it;
        }

        it = 0;

        while ((cur_happ < des_mood_p) && (it < i))
        {
            cur_happ += nums[it];
            cur_quant_music += 1;
            ++it;
        }

        if(cur_quant_music < answer_quant)
        {
            answer_quant = cur_quant_music;
            answer_position = i + 1;
        }
    }

    cout << answer_position << " " << answer_quant;

    return 0;
}
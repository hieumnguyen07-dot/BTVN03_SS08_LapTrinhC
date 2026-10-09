#include <stdio.h>

struct UserAccount {
    int account_id;
    int plan_type;
    int monthly_fee;
    int remaining_days;
    int active_devices;
    int original_index;
};

int main() {
    struct UserAccount users[100] = {
        {101, 1, 0, 15, 4, 0},
        {102, 2, 300000, -5, 10, 1},
        {103, 2, 300000, 30, 3, 2},
        {104, 0, 50000, 10, 5, 3},
        {105, 1, 120000, 20, 0, 4},
        {106, 2, 300000, 45, 2, 5}
    };
    int n = 6;
    int mrr_before = 0;
    int mrr_after = 0;

    for (int i = 0; i < n; i++) {
        if (users[i].remaining_days > 0 && users[i].plan_type > 0) {
            if (users[i].plan_type == 1) mrr_before += 120000;
            else if (users[i].plan_type == 2) mrr_before += 300000;
        }
    }

    for (int i = 0; i < n; i++) {
        users[i].original_index = i;

        // Quy t?c H?t h?n
        if (users[i].remaining_days <= 0) {
            users[i].plan_type = 0;
            users[i].monthly_fee = 0;
            users[i].remaining_days = 0;
            users[i].active_devices = 1;
        } else {
            int max_dev = 1;
            if (users[i].plan_type == 1) {
                users[i].monthly_fee = 120000;
                max_dev = 2;
            } else if (users[i].plan_type == 2) {
                users[i].monthly_fee = 300000;
                max_dev = 5;
            } else {
                users[i].plan_type = 0;
                users[i].monthly_fee = 0;
                max_dev = 1;
            }

            if (users[i].active_devices <= 0) {
                users[i].active_devices = 1;
            } else if (users[i].active_devices > max_dev) {
                users[i].active_devices = max_dev;
            }
        }
    }

    struct UserAccount active_arr[100];
    struct UserAccount free_arr[100];
    int count_active = 0;
    int count_free = 0;

    for (int i = 0; i < n; i++) {
        if (users[i].plan_type > 0) {
            active_arr[count_active++] = users[i];
        } else {
            free_arr[count_free++] = users[i];
        }
    }

    for (int i = 1; i < count_active; i++) {
        struct UserAccount key = active_arr[i];
        int j = i - 1;
        while (j >= 0 && (active_arr[j].monthly_fee < key.monthly_fee || 
              (active_arr[j].monthly_fee == key.monthly_fee && active_arr[j].original_index > key.original_index))) {
            active_arr[j + 1] = active_arr[j];
            j = j - 1;
        }
        active_arr[j + 1] = key;
    }

    int idx = 0;
    for (int i = 0; i < count_active; i++) {
        users[idx++] = active_arr[i];
        mrr_after += active_arr[i].monthly_fee;
    }
    for (int i = 0; i < count_free; i++) {
        users[idx++] = free_arr[i];
    }

    printf("-----------------------------------------------------------------------------------------\n");
    printf("| ID  | Plan Type | Monthly Fee (VNND) | Remaining Days | Active Devices | Status       |\n");
    printf("-----------------------------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        char* status = (users[i].plan_type == 0) ? "Free / Downgraded" : "Active Paid";
        printf("| %-3d | %-9d | %-18d | %-14d | %-14d | %-12s |\n",
               users[i].account_id,
               users[i].plan_type,
               users[i].monthly_fee,
               users[i].remaining_days,
               users[i].active_devices,
               status);
    }
    printf("-----------------------------------------------------------------------------------------\n");

    printf("BAO CAO DOANH THU MRR \n");
    printf("- Tong MRR truoc kiem toan : %d VNND\n", mrr_before);
    printf("- Tong MRR sau kiem toan  : %d VNND\n", mrr_after);
    printf("- Chenh lech doanh thu    : %d VNND\n", mrr_after - mrr_before);

    return 0;
}

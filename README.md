# Jump Only

![image](https://github.com/user-attachments/assets/ce188aee-9cdb-474b-ae5c-075441978f55)

Video giải thích về code và hướng dẫn chơi : [Video](https://drive.google.com/file/d/1bENQcU_DE0Ugfbklx-VwjmQD9q99jMVT/view?usp=drive_link)



## Mục lục

1. [Giới thiệu](#giới-thiệu)
2. [Cách tải game](#cách-tải-game)
3. [Các màn chơi](#các-màn-chơi)
4. [Thành phần trong game](#thành-phần-trong-game)
5. [Cách chơi](#cách-chơi)
6. [Đồ họa & Âm thanh](#đồ-họa--âm-thanh)
7. [Mẹo](#mẹo)
8. [Cấu trúc mã nguồn](#cấu-trúc-mã-nguồn)
9. [Tổng kết](#tổng-kết)

## Giới thiệu

Jump Only là tựa game 2D platformer hành động đơn giản, nơi bạn hòa mình vào nhân vật để nhảy qua các chướng ngại vật bất ngờ xuất hiện.
Game được lấy cảm hứng từ “Jump Only” và “Geometry Dash”. Nhịp độ nhanh giúp rèn luyện phản xạ cực tốt – chỉ cần sai một li là phải chơi lại từ đầu!

![image](https://github.com/user-attachments/assets/a2030327-e633-43bb-93da-1e4023b6fc3f)


## Cách tải game
- Cách 1 :

   - Chạy file main.exe để chơi hoặc
   - Sử dụng [mingw64](https://www.mingw-w64.org/) và các thư viện [SDL2](https://www.libsdl.org/) đi kèm để build file main.cpp. Chạy file vừa build được để chơi.
   - Khuyến cáo sử dụng Visual Studio 2022 hoặc các IDE có khả năng đọc file cmake.

- Cách 2 :

   - Tải file [mingw64](https://www.mingw-w64.org/)
   - Tải file zip từ [File tải game](https://drive.google.com/file/d/1RO7faRUJTYL2g-p7TLXjPP25oVAy9ckv/view?usp=drive_link)
   - Giải nén file và mở file .exe sau đó tận hưởng game thôi.

## Các màn chơi

- Bạn có 3 màn chơi chính với độ khó tăng dần:
    - Màn 1: né các vật cản và gai nhọn (giúp làm quen với chuyển động)
    - Màn 2: tương tự màn 1 nhưng vật cản nhiều hơn
    - Màn 3: độ khó rất cao, yêu cầu phản xạ và kỹ năng né đỉnh cao


## Thành phần trong game

- Character: ![image](https://github.com/user-attachments/assets/66e759c3-58e3-43c3-82a2-c64bc7eb7dbf)

- Trọng lực: nhân vật luôn rơi – nếu không nhảy kịp sẽ rớt
 
- Chướng ngại:
   - Bánh răng cưa ![image](https://github.com/user-attachments/assets/c3e6807a-c501-47b5-8456-1edc3e6761a8)
   - Quả cầu gai ![image](https://github.com/user-attachments/assets/cec27afe-d549-46c5-82b2-8c0dca3f1757)
   - Tường gai ![image](https://github.com/user-attachments/assets/33d357f2-97de-4ba7-a076-04686e2c1e3f)

- Vật phẩm:
   - Kim cương ![image](https://github.com/user-attachments/assets/1318fd3b-daba-469a-b245-de75efddfddc)
   - Mạng sống ![image](https://github.com/user-attachments/assets/73b95ccd-395b-41ae-9a3e-dcbbaab5805a)

## Cách chơi

- Phím điều khiển:
   - ⬅ / ➡ : Di chuyển trái / phải
   - ESC: Dừng game
- Cơ chế nhảy:
   - Nhấn một lần = bay một đoạn
   - Nhấn nhiều lần = bay liên tục
- Chiến thắng: Vượt hết chướng ngại và đến đích
- Thất bại: Chạm vào gai, bánh răng,...
- Thu thập sao: Cố gắng gom đủ 3 viên kim cương trong mỗi màn để trở thành Pro Player!

## Đồ họa & Âm thanh

- Đồ họa: từ freepik.com, ChatGPT 
- Âm thanh: từ youtube.com

## Mẹo

- Không nên nhấn giữ phím vì khó kiểm soát di chuyển
- Nếu thua nhiều lần: hãy bình tĩnh, tập luyện và phản xạ sẽ tốt dần lên!

## Cấu trúc mã nguồn

📄 diamond.h / diamond.cpp – Quản lý vị trí vật phẩm trong game

📄 game.h / game.cpp – Hàm chính điều khiển game: vòng lặp, khởi tạo, render
         
📄 level.h / level1.cpp – Xây dựng màn chơi 1

📄 level.h / level2.cpp – Xây dựng màn chơi 2

📄 level.h / level3.cpp – Xây dựng màn chơi 3

📄 main.cpp – Điểm bắt đầu chương trình

📄 menu.h / menu.cpp – Xây dựng tính năng menu

📄 pause.h / pause.cpp – Xây dựng tính năng dừng game

📄 player.h / player.cpp – Điều khiển nhảy, xử lý chuyển động nhân vật
     

## Tổng kết

Jump Only là một tựa game platformer nhanh và thú vị giúp bạn thư giãn sau giờ học/làm việc. Rèn luyện phản xạ, tính toán điểm rơi và… đôi chút may mắn 😄
Nếu bạn đã phá đảo cả 3 màn – xin chúc mừng: bạn là cao thủ phản xạ đích thực 🔥🔥🔥

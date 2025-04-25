# Jump Only
 
![image](https://github.com/user-attachments/assets/ce188aee-9cdb-474b-ae5c-075441978f55)


Link giải thích về code và hướng dẫn chơi :

________________________________________
#  Giới thiệu

Jump Only là tựa game 2D platformer hành động đơn giản, nơi bạn hòa mình vào nhân vật để nhảy qua các chướng ngại vật bất ngờ xuất hiện.
Game được lấy cảm hứng từ “Jump Only” và “Geometry Dash”. Nhịp độ nhanh giúp rèn luyện phản xạ cực tốt – chỉ cần sai một li là phải chơi lại từ đầu!

 ![image](https://github.com/user-attachments/assets/a2030327-e633-43bb-93da-1e4023b6fc3f)
 

________________________________________
# Các màn chơi

Bạn có 3 màn chơi chính với độ khó tăng dần:
•	Màn 1: né các vật cản và gai nhọn (giúp làm quen với chuyển động)
•	Màn 2: tương tự màn 1 nhưng vật cản nhiều hơn
•	Màn 3: độ khó rất cao, yêu cầu phản xạ và kỹ năng né đỉnh cao
________________________________________
# Bắt đầu chơi

•	Mở game → Chọn Play
•	Chọn Level
•	Vào game và tận hưởng
________________________________________
# Thành phần trong game

•	Character: ![image](https://github.com/user-attachments/assets/66e759c3-58e3-43c3-82a2-c64bc7eb7dbf)

 
•	Trọng lực: nhân vật luôn rơi – nếu không nhảy kịp sẽ rớt
•	Chướng ngại:
  o	Bánh răng cưa ![image](https://github.com/user-attachments/assets/c3e6807a-c501-47b5-8456-1edc3e6761a8)
  
   
  o	Quả cầu gai ![image](https://github.com/user-attachments/assets/cec27afe-d549-46c5-82b2-8c0dca3f1757)
  
   
  o	Tường gai  ![image](https://github.com/user-attachments/assets/33d357f2-97de-4ba7-a076-04686e2c1e3f)

 
•	Vật phẩm:
  o	Kim cương ![image](https://github.com/user-attachments/assets/1318fd3b-daba-469a-b245-de75efddfddc)
  
   
  o	Mạng sống ![image](https://github.com/user-attachments/assets/73b95ccd-395b-41ae-9a3e-dcbbaab5805a)

 
•	Tính năng phụ:
  o	Nhấn ESC để mở Pause menu

![image](https://github.com/user-attachments/assets/a919d000-7d8b-463e-b195-8ed74afb173d)

 
  o	Nhấn “Play” để tiếp tục
  o	Nhấn “Restart” để chơi lại màn đó
  o	Nhấn “Options” để chỉnh âm thanh
  o	Nhấn “Quit” để về menu chính
________________________________________
# Cách chơi

•	Phím điều khiển:
o	⬅ / ➡ : Di chuyển trái / phải
o	ESC: Dừng game
•	Cơ chế nhảy:
o	Nhấn một lần = bay một đoạn
o	Nhấn nhiều lần = bay liên tục
•	Chiến thắng: Vượt hết chướng ngại và đến đích
•	Thất bại: Chạm vào gai, bánh răng,...
•	Thu thập sao: Cố gắng gom đủ 3 viên kim cương trong mỗi màn để trở thành Pro Player!
________________________________________
#  Đồ họa & Âm thanh

•	Đồ họa: từ freepik.com, ChatGPT và ảnh tự chỉnh sửa
•	Âm thanh: từ youtube.com
________________________________________
#  Mẹo

•	Không nên nhấn giữ phím vì khó kiểm soát di chuyển
•	Nếu thua nhiều lần: hãy bình tĩnh, tập luyện và phản xạ sẽ tốt dần lên!
________________________________________
#  Cấu trúc mã nguồn

  📦 Hoc_SDL
     📂 Header Files (.h) – Khai báo biến & hàm dùng chung
       📄 diamond.h – Biến & các hàm xử lý vật phẩm trong game.
       📄 game.h – Biến toàn cục: màn chơi, camera, nhạc nền, renderer...
       📄 level.h – Biến, thông số vật cản và hàm xử lý chung cho các level
       📄 menu.h – Biến và hàm xử lý menu & nút bấm giao diện chính
       📄 pause.h – Biến và hàm xử lý trạng thái dừng game
       📄 player.h – Biến và hàm xử lý nhân vật chính
     📂 Source Files (.cpp) – Chứa toàn bộ logic game
       📄 diamond.cpp – Quản lý vị trí vật phẩm trong game
       📄 game.cpp – Hàm chính điều khiển game: vòng lặp, khởi tạo, render
       📄 level1.cpp – Xây dựng màn chơi 1
       📄 level2.cpp – Xây dựng màn chơi 2
       📄 level3.cpp – Xây dựng màn chơi 3
       📄 main.cpp – Điểm bắt đầu chương trình
       📄 menu.cpp – Xây dựng tính năng menu
       📄 pause.cpp – Xây dựng tính năng dừng game
       📄 player.cpp – Điều khiển nhảy, xử lý chuyển động nhân vật
________________________________________
# Tổng kết

Jump Only là một tựa game platformer nhanh và thú vị giúp bạn thư giãn sau giờ học/làm việc. Rèn luyện phản xạ, tính toán điểm rơi và… đôi chút may mắn 😄
Nếu bạn đã phá đảo cả 3 màn – xin chúc mừng: bạn là cao thủ phản xạ đích thực!!! 🔥🔥🔥


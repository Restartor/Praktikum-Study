def melakukan_kegiatan(kegiatan):
    if kegiatan == "makan":
        return "saya sedang makan."
    elif kegiatan == "minum":
        return "saya sedang minum."
    elif kegiatan == "tidur":
        return "saya sedang tidur."

def manusia(haus, lapar, mengantuk):
    if haus and lapar and mengantuk:
        return "Saya sangat lelah, saya perlu istirahat dan makan serta minum."
    elif haus and lapar:
        return "Saya perlu makan dan minum."
    elif haus and mengantuk:
        return "Saya perlu minum dan istirahat."
    elif lapar and mengantuk:
        return "Saya perlu makan dan istirahat."
    elif haus:
        return "Saya perlu minum."
    elif lapar:
        return "Saya perlu makan."
    elif mengantuk:
        return "Saya perlu istirahat."
    else:
        return "Saya merasa baik-baik saja."

def evaluasi_kegiatan(kegiatan):
    if kegiatan == "makan":
        return "Saya sudah kenyang setelah makan."
    elif kegiatan == "minum":
        return "Saya sudah tidak haus setelah minum."
    elif kegiatan == "tidur":
        return "Saya merasa segar setelah tidur."
    else:
        return "Kegiatan tidak dikenali."

input_haus = input("Apakah anda haus? (ya/tidak):").strip().lower() == 'ya'
input_lapar = input("Apakah anda lapar? (ya/tidak):").strip().lower() == 'ya'
input_mengantuk = input("Apakah anda mengantuk? (ya/tidak):").strip().lower() == 'ya'

rekomendasi = manusia(input_haus, input_lapar, input_mengantuk)
print("Rekomendasi : ", rekomendasi) # rekomendasi ngapain sesuai kondisi manusia

jawaban_kegiatan = input("Apakah anda ingin melakukan suatu kegiatan? (makan/minum/tidur): ").strip().lower()
if jawaban_kegiatan in ['makan',  'minum', 'tidur']:
    hasil_kegiatan = melakukan_kegiatan(jawaban_kegiatan)
    print( "Status kegiatan : ", hasil_kegiatan)
else:
    print("Kegiatan Tidak dikenali")

hasil_evaluasi = evaluasi_kegiatan(jawaban_kegiatan)
print("Evaluasi kegiatan : ", hasil_evaluasi)
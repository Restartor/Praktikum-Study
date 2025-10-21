def lukalcerbanget(kalcer: bool) -> bool:
    if kalcer == True:
        print("lu kalcer banget boskuh")
        return True
    else:
        print("lu ga kalcer boskuh")
        return False


input_value = input("Apakah lu kalcer? (ya/tidak): ")
if input_value.lower() == 'ya':
    lukalcerbanget(True)
elif input_value.lower() == 'tidak':
    lukalcerbanget(False)
else:
    print("Input tidak valid, masukkan 'ya' atau 'tidak'.")
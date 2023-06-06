from cx_Freeze import setup, Executable

setup(
    name="Main",
    version="1.0",
    description="Descrição do Aplicativo",
    executables=[Executable("main.py")]
)
import streamlit as st
import requests

def main():
    st.title("Language Model Streamlit App")
    input_text = st.text_area("Enter text for prediction:")
    if st.button("Predict"):
        if input_text:
            # Send the input_text to the Flask endpoint for prediction
            response = requests.post("http://localhost:5000/predict", json={"text": input_text})
            if response.status_code == 200:
                result = response.json().get("result")
                st.write("Prediction:")
                st.write(result)
            else:
                st.error("Error: Unable to get prediction.")
        else:
            st.warning("Please enter some text for prediction.")
         
if __name__ == "__main__":
    main()

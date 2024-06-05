<?php


namespace page;


class WorkTypeDelete extends WorkType
{


	const string ACTION_CONFIRMATION = "confirmation";

	const string ACTION_PROCESSING = "processing";


	function getContentMain(): ?\iw\dom\Element
	{
		$dom= null;
		if($this->detectProcess()== self::ACTION_PROCESSING) {
			$dom= null;
		} else {

			// Confirmation
			$this->getWorkTypeId();
			$dom= $this->domConfirmation();
		}

		return $this->dom->div(N, $dom);
	}


	private function detectProcess(): string
	{
		return match ($this->uriMatches[2] ?? null) {
			"processing" => self::ACTION_PROCESSING,
			default => self::ACTION_CONFIRMATION,
		};
	}


	private function domConfirmation(): array
	{
		return [
			$this->dom->p(N, "Opravdu chcete tento ty práce smazat?"),
			$this->domButtonBack(),
			$this->domButtonConfirm()
		];
	}


	private function domButtonBack(): \iw\dom\Element
	{
		return $this->dom->a(N, urlBasePage. "/workType/{$this->workTypeId}", "nemazat");
	}


	private function domButtonConfirm(): \iw\dom\Element
	{
		return $this->dom->a(N, urlBasePage. "/workType/{$this->workTypeId}", "ano, smazat");
	}


}